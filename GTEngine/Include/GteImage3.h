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
class Image3 : public Image
{
public:
    // The default constructor creates a null image.  You can resize the image
    // later with an explicit Resize call, an assignment, or by loading the
    // image from disk.
    virtual ~Image3();
    Image3();

    // Copy the input image using the assignment operator.
    Image3(Image3 const& image);

    // The input dimensions must be positive; otherwise, a null image is
    // created.
    Image3(int dimension0, int dimension1, int dimension2);

    // If the input image is compatible with 'this', a copy of the input
    // image data occurs.  If the input image is not compatible, 'this' is
    // recreated to be a copy of 'image'.
    Image3& operator= (Image3 const& image);

    // The input array must have the correct number of pixels as determined by
    // the image parameters.  Use at your own risk, because we cannot verify
    // the compatibility.
    virtual void SetRawPixels(char* rawPixels);

    // Conversion between 1-dimensional indices and 2-dimensional coordinates.
    inline size_t GetIndex(int x, int y, int z) const;
    inline size_t GetIndex(std::array<int, 3> const& coord) const;
    inline void GetCoordinates(size_t index, int& x, int& y, int& z) const;
    inline std::array<int, 3> GetCoordinates(size_t index) const;

    // Access the data as a 1-dimensional array.  The operator[] functions
    // test for valid i in debug configurations and assert on invalid i.  The
    // Get() functions test for valid i and clamp when invalid (debug and
    // release); these functions cannot fail.
    inline PixelType* GetPixels1D() const;
    inline PixelType& operator[] (size_t i);
    inline PixelType const& operator[] (size_t i) const;
    PixelType& Get(size_t i);
    PixelType const& Get(size_t i) const;

    // Access the data as a 3-dimensional array.  Pixel (x,y,z) is accessed
    // as "pixels3D[z][y][x]".  The operator() functions test for valid
    // (x,y,z) in debug configurations and assert on invalid (x,y,z).  The
    // Get() functions test for valid (x,y,z) and clamp when invalid (debug
    // and release); these functions cannot fail.
    inline PixelType*** GetPixels3D() const;
    inline PixelType& operator() (int x, int y, int z);
    inline PixelType const& operator() (int x, int y, int z) const;
    inline PixelType& operator() (std::array<int, 3> const& coord);
    inline PixelType const& operator() (std::array<int,3> const& coord) const;
    inline PixelType& Get(int x, int y, int z);
    inline PixelType const& Get(int x, int y, int z) const;
    inline PixelType& Get(std::array<int, 3> coord);
    inline PixelType const& Get(std::array<int, 3> coord) const;

    // In the following discussion, u, v and w are in {-1,1}.  Given a voxel
    // (x,y,z), the 6-connected neighbors have relative offsets (u,0,0),
    // (0,v,0), and (0,0,w).  The 18-connected neighbors include the
    // 6-connected neighbors and have additional relative offsets (u,v,0),
    // (u,0,w), and (0,v,w).  The 26-connected neighbors include the
    // 18-connected neighbors and have additional relative offsets (u,v,w).
    // The corner neighbors have offsets (0,0,0), (1,0,0), (0,1,0), (1,1,0),
    // (0,0,1), (1,0,1), (0,1,1), and (1,1,1) in that order.  The full
    // neighborhood is the set of 3x3x3 pixels centered at (x,y).

    // The neighborhoods can be accessed as 1-dimensional indices using these
    // functions.  The first five functions provide 1-dimensional indices
    // relative to any voxel location; these depend only on the image
    // dimensions.  The last five functions provide 1-dimensional indices
    // for the actual voxels in the neighborhood; no clamping is used when
    // (x,y,z) is on the boundary.
    void GetNeighborhood(std::array<int, 6>& nbr) const;
    void GetNeighborhood(std::array<int, 18>& nbr) const;
    void GetNeighborhood(std::array<int, 26>& nbr) const;
    void GetCorners(std::array<int, 8>& nbr) const;
    void GetFull(std::array<int, 27>& nbr) const;
    void GetNeighborhood(int x, int y, int z,
        std::array<size_t, 6>& nbr) const;
    void GetNeighborhood(int x, int y, int z,
        std::array<size_t, 18>& nbr) const;
    void GetNeighborhood(int x, int y, int z,
        std::array<size_t, 26>& nbr) const;
    void GetCorners(int x, int y, int z,
        std::array<size_t, 8>& nbr) const;
    void GetFull(int x, int y, int z,
        std::array<size_t, 27>& nbr) const;

    // The neighborhoods can be accessed as 3-tuples using these functions.
    // The first five functions provide 3-tuples relative to any voxel
    // location; these depend only on the image dimensions.  The last five
    // functions provide 3-tuples for the actual voxels in the neighborhood;
    // no clamping is used when (x,y,z) is on the boundary.
    void GetNeighborhood(std::array<std::array<int, 3>, 6>& nbr) const;
    void GetNeighborhood(std::array<std::array<int, 3>, 18>& nbr) const;
    void GetNeighborhood(std::array<std::array<int, 3>, 26>& nbr) const;
    void GetCorners(std::array<std::array<int, 3>, 8>& nbr) const;
    void GetFull(std::array<std::array<int, 3>, 27>& nbr) const;
    void GetNeighborhood(int x, int y, int z,
        std::array<std::array<size_t, 3>, 6>& nbr) const;
    void GetNeighborhood(int x, int y, int z,
        std::array<std::array<size_t, 3>, 18>& nbr) const;
    void GetNeighborhood(int x, int y, int z,
        std::array<std::array<size_t, 3>, 26>& nbr) const;
    void GetCorners(int x, int y, int z,
        std::array<std::array<size_t, 3>, 8>& nbr) const;
    void GetFull(int x, int y, int z,
        std::array<std::array<size_t, 3>, 27>& nbr) const;

    // Resize an image.  All data is lost from the original image.  The
    // function is convenient for taking a default-constructed image and
    // setting its dimension once it is known.  This avoids an irrelevant
    // memory copy that occurs if instead you were to use the statement
    // image = Image1<PixelType>(dimension0, dimension1, dimension2).  The
    // return value is 'true' whenever the image is resized (reallocations
    // occurred).
    bool Resize(int dimension0, int dimension1, int dimension2);

    // Set all pixels to the specified value.
    void SetAllPixels(PixelType const& value);

    // The required dimensions and pixel type are that of the current image
    // object.
    bool Load(std::string const& filename);

private:
    void AllocatePointers();
    void DeallocatePointers();

    // Typed pointers to Image::mRawPixels.
    PixelType*** mPixels;

    // Uninitialized, used in the Get(int) calls.
    PixelType mInvalidPixel;
};

#include "GteImage3.inl"

}
