// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/25)

#pragma once

#include "GteImage.h"
#include "GteLogger.h"
#include <array>
#include <type_traits>

namespace gte
{

// The PixelType must be trivially copyable.  We used to have static_assert
// statements to enforce this, but Fedora 20 with gcc 4.8.2 has not yet
// implemented std::is_trivially_copyable.

template <typename PixelType>
class Image2 : public Image
{
public:
    // The default constructor creates a null image.  You can resize the image
    // later with an explicit Resize call, an assignment, or by loading the
    // image from disk.
    virtual ~Image2();
    Image2();

    // Copy the input image using the assignment operator.
    Image2(Image2 const& image);

    // The input dimensions must be positive; otherwise, a null image is
    // created.
    Image2(int dimension0, int dimension1);

    // If the input image is compatible with 'this', a copy of the input
    // image data occurs.  If the input image is not compatible, 'this' is
    // recreated to be a copy of 'image'.
    Image2& operator= (Image2 const& image);

    // The input array must have the correct number of pixels as determined by
    // the image parameters.  Use at your own risk, because we cannot verify
    // the compatibility.
    virtual void SetRawPixels(char* rawPixels);

    // Conversion between 1-dimensional indices and 2-dimensional coordinates.
    inline size_t GetIndex(int x, int y) const;
    inline size_t GetIndex(std::array<int, 2> const& coord) const;
    inline void GetCoordinates(size_t index, int& x, int& y) const;
    inline std::array<int, 2> GetCoordinates(size_t index) const;

    // Access the data as a 1-dimensional array.  The operator[] functions
    // test for valid i in debug configurations and assert on invalid i.  The
    // Get() functions test for valid i and clamp when invalid (debug and
    // release); these functions cannot fail.
    inline PixelType* GetPixels1D() const;
    inline PixelType& operator[] (size_t i);
    inline PixelType const& operator[] (size_t i) const;
    PixelType& Get(size_t i);
    PixelType const& Get(size_t i) const;

    // Access the data as a 2-dimensional array.  Pixel (x,y) is accessed
    // as "pixels2D[y][x]".  The operator() functions test for valid (x,y) in
    // debug configurations and assert on invalid (x,y).  The Get() functions
    // test for valid (x,y) and clamp when invalid (debug and release); these
    // functions cannot fail.
    inline PixelType** GetPixels2D() const;
    inline PixelType& operator() (int x, int y);
    inline PixelType const& operator() (int x, int y) const;
    inline PixelType& operator() (std::array<int, 2> const& coord);
    inline PixelType const& operator() (std::array<int,2> const& coord) const;
    inline PixelType& Get(int x, int y);
    inline PixelType const& Get(int x, int y) const;
    inline PixelType& Get(std::array<int, 2> coord);
    inline PixelType const& Get(std::array<int, 2> coord) const;

    // In the following discussion, u and v are in {-1,1}.  Given a pixel
    // (x,y), the 4-connected neighbors have relative offsets (u,0) and
    // (0,v).  The 8-connected neighbors include the 4-connected neighbors
    // and have additional relative offsets (u,v).  The corner neighbors
    // have relative offsets (0,0), (1,0), (0,1), and (1,1) in that order.
    // The full neighborhood is the set of 3x3 pixels centered at (x,y).

    // The neighborhoods can be accessed as 1-dimensional indices using these
    // functions.  The first four functions provide 1-dimensional indices
    // relative to any pixel location; these depend only on the image
    // dimensions.  The last four functions provide 1-dimensional indices
    // for the actual pixels in the neighborhood; no clamping is used when
    // (x,y) is on the boundary.
    void GetNeighborhood(std::array<int, 4>& nbr) const;
    void GetNeighborhood(std::array<int, 8>& nbr) const;
    void GetCorners(std::array<int, 4>& nbr) const;
    void GetFull(std::array<int, 9>& nbr) const;
    void GetNeighborhood(int x, int y, std::array<size_t, 4>& nbr) const;
    void GetNeighborhood(int x, int y, std::array<size_t, 8>& nbr) const;
    void GetCorners(int x, int y, std::array<size_t, 4>& nbr) const;
    void GetFull(int x, int y, std::array<size_t, 9>& nbr) const;

    // The neighborhoods can be accessed as 2-tuples using these functions.
    // The first four functions provide 2-tuples relative to any pixel
    // location; these depend only on the image dimensions.  The last four
    // functions provide 2-tuples for the actual pixels in the neighborhood;
    // no clamping is used when (x,y) is on the boundary.
    void GetNeighborhood(std::array<std::array<int, 2>, 4>& nbr) const;
    void GetNeighborhood(std::array<std::array<int, 2>, 8>& nbr) const;
    void GetCorners(std::array<std::array<int, 2>, 4>& nbr) const;
    void GetFull(std::array<std::array<int, 2>, 9>& nbr) const;
    void GetNeighborhood(int x, int y,
        std::array<std::array<size_t, 2>, 4>& nbr) const;
    void GetNeighborhood(int x, int y,
        std::array<std::array<size_t, 2>, 8>& nbr) const;
    void GetCorners(int x, int y,
        std::array<std::array<size_t, 2>, 4>& nbr) const;
    void GetFull(int x, int y,
        std::array<std::array<size_t, 2>, 9>& nbr) const;

    // Resize an image.  All data is lost from the original image.  The
    // function is convenient for taking a default-constructed image and
    // setting its dimension once it is known.  This avoids an irrelevant
    // memory copy that occurs if instead you were to use the statement
    // image = Image1<PixelType>(dimension0, dimension1).  The return value
    // is 'true' whenever the image is resized (reallocations occurred).
    bool Resize(int dimension0, int dimension1);

    // Set all pixels to the specified value.
    void SetAllPixels(PixelType const& value);

    // The required dimensions and pixel type are that of the current image
    // object.
    bool Load(std::string const& filename);

private:
    void AllocatePointers();
    void DeallocatePointers();

    // Typed pointers to Image::mRawPixels.
    PixelType** mPixels;

    // Uninitialized, used in the Get(int) calls.
    PixelType mInvalidPixel;
};

#include "GteImage2.inl"

}
