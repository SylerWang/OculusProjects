// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline std::string const& DataFormat::GetName(DFType type)
{
    return msName[type];
}
//----------------------------------------------------------------------------
inline unsigned int DataFormat::GetNumBytesPerStruct(DFType type)
{
    return msNumBytesPerStruct[type];
}
//----------------------------------------------------------------------------
inline unsigned int DataFormat::GetNumChannels(DFType type)
{
    return msNumChannels[type];
}
//----------------------------------------------------------------------------
inline DFChannelType DataFormat::GetChannelType(DFType type)
{
    return msChannelType[type];
}
//----------------------------------------------------------------------------
inline bool DataFormat::ConvertChannel(DFType type)
{
    return msConvertChannel[type];
}
//----------------------------------------------------------------------------
inline bool DataFormat::IsSupported(DFType type)
{
    return msSupported[type];
}
//----------------------------------------------------------------------------
inline bool DataFormat::IsDepth(DFType type)
{
    return type == DF_D32_FLOAT_S8X24_UINT
        || type == DF_D32_FLOAT
        || type == DF_D24_UNORM_S8_UINT
        || type == DF_D16_UNORM;
}
//----------------------------------------------------------------------------
