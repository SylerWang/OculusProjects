// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "FileVideoStream.h"
using namespace gte;

//----------------------------------------------------------------------------
FileVideoStream::~FileVideoStream()
{
    mInput.close();
}
//----------------------------------------------------------------------------
FileVideoStream::FileVideoStream(std::string const& filename,
    DX11Engine* engine)
    :
    VideoStream(engine),
    mFilename(filename),
    mNumImages(0),
    mCurrentImage(0)
{
    mInput.open(filename, std::ios::in | std::ios::binary);
    mInput.read((char*)&mNumImages, sizeof(mNumImages));
    mInput.read((char*)&mType, sizeof(mType));
    mInput.read((char*)&mWidth, sizeof(mWidth));
    mInput.read((char*)&mHeight, sizeof(mHeight));

    mBuffer.resize(mWidth*mHeight*DataFormat::GetNumBytesPerStruct(mType));
}
//----------------------------------------------------------------------------
std::string const& FileVideoStream::GetFilename() const
{
    return mFilename;
}
//----------------------------------------------------------------------------
unsigned int FileVideoStream::GetNumImages() const
{
    return mNumImages;
}
//----------------------------------------------------------------------------
char* FileVideoStream::GetImage()
{
    mInput.read((char*)&mFrame.number, sizeof(mFrame.number));
    mInput.read(&mBuffer[0], mBuffer.size());
    if (++mCurrentImage == mNumImages)
    {
        mCurrentImage = 0;
        mInput.seekg(0);
    }
    return &mBuffer[0];
}
//----------------------------------------------------------------------------
