// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteTexture2.h"
#include <guiddef.h>

namespace gte
{

class GTE_IMPEXP WICFileIO
{
public:
    // Support for loading from BMP, GIF, ICON, JPEG, PNG, and TIFF.
    // The returned texture has a format that matches as close as possible
    // the format on disk.  If a matching format is not found, the returned
    // texture is an R8G8B8A8 format with texels converted from the source
    // format.
    static Texture2* Load(std::string const& filename, bool wantMipmaps);

    // Support for saving to PNG format.  Currently, the only formats
    // supported are R8G8B8A8 and R16.
    static bool SaveToPNG(std::string const& filename, Texture2* texture);

private:
    class ComInitializer
    {
    public:
        ~ComInitializer();
        ComInitializer();
        bool IsInitialized() const;
    private:
        bool mInitialized;
    };

    struct LoadFormatMap
    {
        DFType gtFormat;
        GUID const* wicInputGUID;
        GUID const* wicConvertGUID;
    };
    enum { NUM_LOAD_FORMATS = 14 };
    static LoadFormatMap const msLoadFormatMap[NUM_LOAD_FORMATS];

    struct SaveFormatMap
    {
        DFType gtFormat;
        GUID const* wicOutputGUID;
    };
    enum { NUM_SAVE_FORMATS = 11 };
    static SaveFormatMap const msSaveFormatMap[NUM_SAVE_FORMATS];
};

}
