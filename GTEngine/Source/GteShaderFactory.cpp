// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteShaderFactory.h"
#include <regex>
using namespace gte;

//----------------------------------------------------------------------------
VertexShader* ShaderFactory::CreateVertex(std::string const& filename,
    HLSLDefiner const& definer, std::string const& entry,
    std::string const& target, unsigned int flags)
{
    Shader* shader = Create(filename, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_VERTEX_SHADER)
    {
        return static_cast<VertexShader*>(shader);
    }
    else
    {
        LogError("CreateVertex failed for file " + filename + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
PixelShader* ShaderFactory::CreatePixel(std::string const& filename,
    HLSLDefiner const& definer, std::string const& entry,
    std::string const& target, unsigned int flags)
{
    Shader* shader = Create(filename, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_PIXEL_SHADER)
    {
        return static_cast<PixelShader*>(shader);
    }
    else
    {
        LogError("CreatePixel failed for file " + filename + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
GeometryShader* ShaderFactory::CreateGeometry(std::string const& filename,
    HLSLDefiner const& definer, std::string const& entry,
    std::string const& target, unsigned int flags)
{
    Shader* shader = Create(filename, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_GEOMETRY_SHADER)
    {
        return static_cast<GeometryShader*>(shader);
    }
    else
    {
        LogError("CreateGeometry failed for file " + filename + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
ComputeShader* ShaderFactory::CreateCompute(std::string const& filename,
    HLSLDefiner const& definer, std::string const& entry,
    std::string const& target, unsigned int flags)
{
    Shader* shader = Create(filename, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_COMPUTE_SHADER)
    {
        return static_cast<ComputeShader*>(shader);
    }
    else
    {
        LogError("CreateCompute failed for file " + filename + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
VertexShader* ShaderFactory::CreateVertex(std::string const& name,
    std::string const& source, HLSLDefiner const& definer,
    std::string const& entry, std::string const& target,
    unsigned int flags)
{
    Shader* shader = Create(name, source, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_VERTEX_SHADER)
    {
        return static_cast<VertexShader*>(shader);
    }
    else
    {
        LogError("CreateVertex failed for string " + name + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
PixelShader* ShaderFactory::CreatePixel(std::string const& name,
    std::string const& source, HLSLDefiner const& definer,
    std::string const& entry, std::string const& target,
    unsigned int flags)
{
    Shader* shader = Create(name, source, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_PIXEL_SHADER)
    {
        return static_cast<PixelShader*>(shader);
    }
    else
    {
        LogError("CreatePixel failed for string " + name + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
GeometryShader* ShaderFactory::CreateGeometry(std::string const& name,
    std::string const& source, HLSLDefiner const& definer,
    std::string const& entry, std::string const& target,
    unsigned int flags)
{
    Shader* shader = Create(name, source, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_GEOMETRY_SHADER)
    {
        return static_cast<GeometryShader*>(shader);
    }
    else
    {
        LogError("CreateGeometry failed for string " + name + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
ComputeShader* ShaderFactory::CreateCompute(std::string const& name,
    std::string const& source, HLSLDefiner const& definer,
    std::string const& entry, std::string const& target,
    unsigned int flags)
{
    Shader* shader = Create(name, source, definer, entry, target, flags);
    if (shader && shader->GetType() == GT_COMPUTE_SHADER)
    {
        return static_cast<ComputeShader*>(shader);
    }
    else
    {
        LogError("CreateCompute failed for string " + name + ".");
        return nullptr;
    }
}
//----------------------------------------------------------------------------
std::string ShaderFactory::MakeShaderString(std::string const& text)
{
    std::regex const token_ifdef("#ifdef( \\S+)");
    std::regex const token_if("#if( \\S+)");
    std::regex const token_else("#else");
    std::regex const token_elif("#elif");
    std::regex const token_endif("#endif");

    std::string result;
    result = std::regex_replace(text, token_ifdef, "\r\n#ifdef$1\r\n");
    result = std::regex_replace(result, token_if, "\r\n#if$1\r\n");
    result = std::regex_replace(result, token_else, "\r\n#else\r\n");
    result = std::regex_replace(result, token_elif, "\r\n#elif\r\n");
    result = std::regex_replace(result, token_endif, "\r\n#endif\r\n");
    return result;
}
//----------------------------------------------------------------------------
Shader* ShaderFactory::Create(std::string const& filename,
    HLSLDefiner const& definer, std::string const& entry,
    std::string const& target, unsigned int flags)
{
    HLSLShader hlsl = HLSLShaderFactory::CreateFromFile(filename, entry,
        target, definer, flags);
    return (hlsl.IsValid() ? new Shader(hlsl) : nullptr);
}
//----------------------------------------------------------------------------
Shader* ShaderFactory::Create(std::string const& name,
    std::string const& source, HLSLDefiner const& definer,
    std::string const& entry, std::string const& target, unsigned int flags)
{
    HLSLShader hlsl = HLSLShaderFactory::CreateFromString(name, source, entry,
        target, definer, flags);
    return (hlsl.IsValid() ? new Shader(hlsl) : nullptr);
}
//----------------------------------------------------------------------------
