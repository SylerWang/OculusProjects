// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "SurfaceExtractionWindow.h"

//----------------------------------------------------------------------------
SurfaceExtractionWindow::~SurfaceExtractionWindow()
{
}
//----------------------------------------------------------------------------
SurfaceExtractionWindow::SurfaceExtractionWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f),
    mLevel(nullptr)
{
    if (!SetEnvironment() || !CreateScene())
    {
        parameters.created = false;
        return;
    }

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(4.0f, 0.0f, 0.0f, 1.0f);
    Vector4<float> camDVector(-1.0f, 0.0f, 0.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    EnableCameraMotion(0.01f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
}
//----------------------------------------------------------------------------
void SurfaceExtractionWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();
    UpdateConstants();

    mEngine->ClearBuffers();

#ifdef USE_DRAW_DIRECT
    // Extract the voxels using a compute shader.
    mDirectVoxels->SetNumActiveElements(0);
    mEngine->Execute(mDirectExtractShader, XGROUPS, YGROUPS, ZGROUPS);

    // Copy the vertices and indices from the GPU to the CPU.  Create a
    // triangle mesh from them.
    CreateMesh();

    if (mDirectMesh)
    {
        // Draw the triangle mesh.
        mEngine->Draw(mDirectMesh.get());
    }

    mEngine->Draw(8, mYSize-24, mTextColor,
        Environment::CreateString("direct: level = %.2f", *mLevel));
#else
    // Extract the voxels using a compute shader.
    mIndirectVoxels->SetNumActiveElements(0);
    mEngine->Execute(mIndirectExtractShader, XGROUPS, YGROUPS, ZGROUPS);

    // Copy from the GPU to the CPU only the number of voxels extracted.
    mEngine->GetNumActiveElements(mIndirectVoxels);
    int numVoxels = mIndirectVoxels->GetNumActiveElements();
    if (numVoxels > 0)
    {
        // Draw the triangle mesh directly from the voxel information
        // that is already on the GPU.
        mVoxelMesh->GetVertexBuffer()->SetNumActiveElements(numVoxels);
        mEngine->Draw(mVoxelMesh);
    }

    mEngine->Draw(8, mYSize-24, mTextColor,
        Environment::CreateString("indirect: level = %.2f", *mLevel));
#endif

    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool SurfaceExtractionWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':  // Toggle solid/wireframe.
    case 'W':
        if (mEngine->GetRasterizerState() == mNoCullSolidState)
        {
            mEngine->SetRasterizerState(mNoCullWireState);
        }
        else
        {
            mEngine->SetRasterizerState(mNoCullSolidState);
        }
        return true;

    case '+':  // Increase the level value for the isosurface.
    case '=':
        *mLevel += 0.01f;
        if (*mLevel > 0.99f)
        {
            *mLevel = 0.99f;
        }
        mEngine->Update(mParametersBuffer);
        return true;

    case '-':  // Decrease the level value for the isosurface.
    case '_':
        *mLevel -= 0.01f;
        if (*mLevel < 0.01f)
        {
            *mLevel = 0.01f;
        }
        mEngine->Update(mParametersBuffer);
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool SurfaceExtractionWindow::SetEnvironment()
{
    std::string gtpath = mEnvironment.GetVariable("GTE_PATH");
    if (gtpath == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(gtpath + 
        "/Samples/Imagics/SurfaceExtraction/Shaders/");

    if (mEnvironment.GetPath("DrawSurfaceIndirect.hlsl") == "")
    {
        LogError("Cannot find file DrawSurfaceIndirect.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ExtractSurface.hlsl") == "")
    {
        LogError("Cannot find file ExtractSurface.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ExtractSurfaceIndirect.hlsl") == "")
    {
        LogError("Cannot find file ExtractSurfaceIndirect.hlsl.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
bool SurfaceExtractionWindow::CreateScene()
{
    CreateSharedResources();
#ifdef USE_DRAW_DIRECT
    return CreateDirectResources();
#else
    return CreateIndirectResources();
#endif
}
//----------------------------------------------------------------------------
void SurfaceExtractionWindow::CreateSharedResources()
{
    // Disable culling.
    mNoCullSolidState.reset(new RasterizerState());
    mNoCullSolidState->cullMode = RasterizerState::CULL_NONE;
    mNoCullSolidState->fillMode = RasterizerState::FILL_SOLID;
    mEngine->SetRasterizerState(mNoCullSolidState);

    // Enable wireframe (when requested).
    mNoCullWireState.reset(new RasterizerState());
    mNoCullWireState->cullMode = RasterizerState::CULL_NONE;
    mNoCullWireState->fillMode = RasterizerState::FILL_WIREFRAME;

    // Create the Marching Cubes table.
    unsigned int const numElements = 256 * 41;
    unsigned int const numBytes = numElements * sizeof(int);
    mLookup.reset(new StructuredBuffer(numElements, sizeof(int)));
    memcpy(mLookup->GetData(), mMarchingCubes.GetTable(), numBytes);

    // Use a Mersenne twister engine for random numbers.
    std::mt19937 mte;
    std::uniform_real_distribution<float> symr(-1.0f, 1.0f);
    std::uniform_real_distribution<float> posr(0.01f, 100.0f);

    // Create an image as a sum of randomly generated Gaussians distributions.
    std::vector<Vector3<float>> mean(NUM_GAUSSIANS);
    std::vector<Matrix3x3<float>> covariance(NUM_GAUSSIANS);
    for (int i = 0; i < NUM_GAUSSIANS; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            mean[i][j] = symr(mte);
            mean[i][j] = symr(mte);
            mean[i][j] = symr(mte);
        }

        Matrix3x3<float> diagonal(posr(mte), posr(mte), posr(mte));
        Quaternion<float> q(symr(mte), symr(mte), symr(mte), symr(mte));
        Normalize(q);
        Matrix3x3<float> rotate = Rotation<3,float>(q);
        covariance[i] = rotate*diagonal*Transpose(rotate);
    }

    float const dx = 2.0f/XBOUND, dy = 2.0f/YBOUND, dz = 2.0f/ZBOUND;
    mImage.reset(new StructuredBuffer(NUM_VOXELS, sizeof(float)));
    float* image = mImage->Get<float>();
    Vector3<float> pos;
    float wmin = std::numeric_limits<float>::max(), wmax = 0.0f;
    for (int z = 0; z < ZBOUND; ++z)
    {
        pos[2] = -1.0f + 2.0f*z/ZBOUND;
        for (int y = 0; y < YBOUND; ++y)
        {
            pos[1] = -1.0f + 2.0f*y/YBOUND;
            for (int x = 0; x < XBOUND; ++x)
            {
                pos[0] = -1.0f + 2.0f*x/XBOUND;

                float w = 0.0f;
                for (int i = 0; i < NUM_GAUSSIANS; ++i)
                {
                    Vector3<float> diff = pos - mean[i];
                    float arg = Dot(diff, covariance[i]*diff);
                    w += exp(-arg);
                }

                *image++ = w;
                if (w > wmax)
                {
                    wmax = w;
                }
                if (w < wmin)
                {
                    wmin = w;
                }
            }
        }
    }

    // Scale to [0,1].
    float invRange = 1.0f/(wmax - wmin);
    image = mImage->Get<float>();
    for (int i = 0; i < NUM_VOXELS; ++i)
    {
        image[i] = (image[i] - wmin)*invRange;
    }

    mParametersBuffer.reset(new ConstantBuffer(4*sizeof(float), true));
    float* param = mParametersBuffer->Get<float>();
    *param++ = dx;
    *param++ = dy;
    *param++ = dz;
    *param = 0.5f;
    mLevel = param;

    mTranslate.SetTranslation(-1.0f, -1.0f, -1.0f);

    mColorTexture.reset(new Texture3(DF_R8G8B8A8_UNORM, 2, 2, 2));
    unsigned int* color = mColorTexture->Get<unsigned int>();
    color[0] = 0xFF000000;
    color[1] = 0xFF0000FF;
    color[2] = 0xFF00FF00;
    color[3] = 0xFF00FFFF;
    color[4] = 0xFFFF0000;
    color[5] = 0xFFFF00FF;
    color[6] = 0xFFFFFF00;
    color[7] = 0xFFFFFFFF;
}
//----------------------------------------------------------------------------
#ifdef USE_DRAW_DIRECT
//----------------------------------------------------------------------------
bool SurfaceExtractionWindow::CreateDirectResources()
{
    // Create the compute shader.
    HLSLDefiner definer;
    definer.SetInt("XBOUND", XBOUND);
    definer.SetInt("YBOUND", YBOUND);
    definer.SetInt("ZBOUND", ZBOUND);
    definer.SetInt("XTHREADS", XTHREADS);
    definer.SetInt("YTHREADS", YTHREADS);
    definer.SetInt("ZTHREADS", ZTHREADS);

    std::string path = mEnvironment.GetPath("ExtractSurface.hlsl");
    mDirectExtractShader.reset(ShaderFactory::CreateCompute(path, definer));
    if (!mDirectExtractShader)
    {
        LogError("Failed to compile ExtractSurface.hlsl.");
        return false;
    }

    // Create the buffer for voxel output.  Because we will read back the
    // voxels every frame, create a persistent staging buffer for the copy
    // (avoids creating/destroying a staging buffer on each read back).
    mDirectVoxels.reset(new StructuredBuffer(NUM_VOXELS,
        sizeof(DirectVoxel)));
    mDirectVoxels->MakeAppendConsume();
    mDirectVoxels->SetCopyType(Resource::COPY_STAGING_TO_CPU);

    // Attach resources to the shader.
    mDirectExtractShader->Set("Parameters", mParametersBuffer);
    mDirectExtractShader->Set("lookup", mLookup);
    mDirectExtractShader->Set("image", mImage);
    mDirectExtractShader->Set("voxels", mDirectVoxels);

    // Create a vertex color effect (for now uses only red).
    mDirectDrawEffect.reset(new Texture3Effect(mColorTexture,
        SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP,
        SamplerState::CLAMP, SamplerState::CLAMP));

    // The mDirectMesh will be created each frame by a call to CreateMesh().
    return true;
}
//----------------------------------------------------------------------------
void SurfaceExtractionWindow::CreateMesh()
{
    mEngine->CopyGpuToCpu(mDirectVoxels);
    DirectVoxel* voxels = mDirectVoxels->Get<DirectVoxel>();
    int numActive = mDirectVoxels->GetNumActiveElements();
    if (numActive <= 0)
    {
        return;
    }

    // Create the mesh.
    std::vector<Vector3<float>> vertices;
    std::vector<int> indices;
    for (int i = 0, vbase = 0; i < numActive; ++i)
    {
        DirectVoxel const& voxel = voxels[i];
        for (int j = 0; j < voxel.numVertices; ++j)
        {
            vertices.push_back(voxel.vertices[j]);
        }

        for (int j = 0; j < 3 * voxel.numTriangles; ++j)
        {
            indices.push_back(vbase + voxel.indices[j]);
        }

        vbase += voxel.numVertices;
    }

    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_TEXCOORD, DF_R32G32B32_FLOAT, 0);
    unsigned int numVertices = static_cast<unsigned int>(vertices.size());
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat,
        numVertices));
    Vertex* v = vbuffer->Get<Vertex>();
    for (unsigned int i = 0; i < numVertices; ++i, ++v)
    {
        v->position = vertices[i];
        v->tcoord = 0.5f*vertices[i];
    }

    unsigned int numTriangles = static_cast<int>(indices.size() / 3);
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_TRIMESH,
        numTriangles, sizeof(unsigned int)));
    memcpy(ibuffer->GetData(), &indices[0], ibuffer->GetNumBytes());

    mDirectMesh.reset(new Visual(vbuffer, ibuffer, mDirectDrawEffect));
}
//----------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------
bool SurfaceExtractionWindow::CreateIndirectResources()
{
    // Create the shaders.
    HLSLDefiner definer;
    definer.SetInt("XBOUND", XBOUND);
    definer.SetInt("YBOUND", YBOUND);
    definer.SetInt("ZBOUND", ZBOUND);
    definer.SetInt("XTHREADS", XTHREADS);
    definer.SetInt("YTHREADS", YTHREADS);
    definer.SetInt("ZTHREADS", ZTHREADS);

    std::string path = mEnvironment.GetPath("ExtractSurfaceIndirect.hlsl");
    mIndirectExtractShader.reset(ShaderFactory::CreateCompute(path, definer));
    if (!mIndirectExtractShader)
    {
        LogError("Failed to compile ExtractSurfaceIndirect.hlsl.");
        return false;
    }

    path = mEnvironment.GetPath("DrawSurfaceIndirect.hlsl");
    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(
        path, definer));
    if (!vshader)
    {
        LogError("Failed to compile vshader of DrawSurfaceIndirect.hlsl.");
        return false;
    }

    std::shared_ptr<GeometryShader> gshader(ShaderFactory::CreateGeometry(
        path, definer));
    if (!vshader)
    {
        LogError("Failed to compile gshader of DrawSurfaceIndirect.hlsl.");
        return false;
    }

    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        path, definer));
    if (!pshader)
    {
        LogError("Failed to compile pshader of DrawSurfaceIndirect.hlsl.");
        return false;
    }

    // Create the vertex and index buffers for SV_VertexID-based drawing.
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(NUM_VOXELS));
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_POLYPOINT,
        NUM_VOXELS));

    // Create the buffer for voxel output and that is used as the actual
    // vertex buffer input.
    mIndirectVoxels.reset(new StructuredBuffer(NUM_VOXELS,
        sizeof(IndirectVoxel)));
    mIndirectVoxels->MakeAppendConsume();

    // Create and attach resources to the shaders.
    mIndirectExtractShader->Set("Parameters", mParametersBuffer);
    mIndirectExtractShader->Set("image", mImage);
    mIndirectExtractShader->Set("voxels", mIndirectVoxels);

    vshader->Set("voxels", mIndirectVoxels);

    mIndirectPVWMatrixBuffer.reset(new ConstantBuffer(
        sizeof(Matrix4x4<float>), true));
    mIndirectPVWMatrix = mIndirectPVWMatrixBuffer->Get<Matrix4x4<float>>();
    *mIndirectPVWMatrix = Matrix4x4<float>::Identity();

    gshader->Set("Parameters", mParametersBuffer);
    gshader->Set("PVWMatrix", mIndirectPVWMatrixBuffer);
    gshader->Set("lookup", mLookup);
    gshader->Set("image", mImage);

    mColorSampler.reset(new SamplerState());
    mColorSampler->filter = SamplerState::MIN_L_MAG_L_MIP_P;
    mColorSampler->mode[0] = SamplerState::CLAMP;
    mColorSampler->mode[1] = SamplerState::CLAMP;
    mColorSampler->mode[2] = SamplerState::CLAMP;

    pshader->Set("colorTexture", mColorTexture);
    pshader->Set("colorSampler", mColorSampler);

    mIndirectDrawEffect.reset(new VisualEffect(vshader, pshader, gshader));

    mVoxelMesh.reset(new Visual(vbuffer, ibuffer, mIndirectDrawEffect));
    return true;
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
void SurfaceExtractionWindow::UpdateConstants()
{
    // Compute the new world transforms and copy to constant buffers.
    Matrix4x4<float> pvMatrix = mCamera.GetProjectionViewMatrix();
#if defined(GTE_USE_MAT_VEC)
    Matrix4x4<float> pvwMatrix = pvMatrix*GetTrackballRotation()*mTranslate;
#else
    Matrix4x4<float> pvwMatrix = mTranslate*GetTrackballRotation()*pvMatrix;
#endif

#ifdef USE_DRAW_DIRECT
    mDirectDrawEffect->SetPVWMatrix(pvwMatrix);
    mEngine->Update(mDirectDrawEffect->GetPVWMatrixConstant());
#else
    *mIndirectPVWMatrix = pvwMatrix;
    mEngine->Update(mIndirectPVWMatrixBuffer);
#endif
}
//----------------------------------------------------------------------------
