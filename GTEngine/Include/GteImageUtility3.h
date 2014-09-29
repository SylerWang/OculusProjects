// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/25)

#pragma once

#include "GTEngineDEF.h"
#include "GteImage3.h"

namespace gte
{

class GTE_IMPEXP ImageUtility3
{
public:
    // All but the Draw* functions are operations on binary images.  Let the
    // image have d0 columns, d1 rows, and d2 slices.  The input image must
    // have zeros on its boundaries x = 0, x = d0-1, y = 0, y = d1-1, z = 0,
    // and z = d2-1.  The 0-valued voxels are considered to be background.
    // The 1-valued voxels are considered to be foreground.  In some of the
    // operations, to save memory and time the input image is modified by the
    // algorithms.  If you need to preserve the input image, make a copy of it
    // before calling these functions.

    // Compute the 6-connected components of a binary image.  The input image
    // is modified to avoid the cost of making a copy.  On output, the image
    // values are the labels for the components.  The array components[k],
    // k >= 1, contains the indices for the k-th component.
    static void GetComponents6(Image3<int>& image,
        std::vector<std::vector<size_t>>& components);

    // Compute the 18-connected components of a binary image.  The input image
    // is modified to avoid the cost of making a copy.  On output, the image
    // values are the labels for the components.  The array components[k],
    // k >= 1, contains the indices for the k-th component.
    static void GetComponents18(Image3<int>& image,
        std::vector<std::vector<size_t>>& components);

    // Compute the 26-connected components of a binary image.  The input image
    // is modified to avoid the cost of making a copy.  On output, the image
    // values are the labels for the components.  The array components[k],
    // k >= 1, contains the indices for the k-th component.
    static void GetComponents26(Image3<int>& image,
        std::vector<std::vector<size_t>>& components);

    // Dilate the image using a structuring element that contains the
    // 6-connected neighbors.
    static void Dilate6(Image3<int> const& inImage, Image3<int>& outImage);

    // Dilate the image using a structuring element that contains the
    // 18-connected neighbors.
    static void Dilate18(Image3<int> const& inImage, Image3<int>& outImage);

    // Dilate the image using a structuring element that contains the
    // 26-connected neighbors.
    static void Dilate26(Image3<int> const& inImage, Image3<int>& outImage);

    // Compute coordinate-directional convex set.  For a given coordinate
    // direction (x, y, or z), identify the first and last 1-valued voxels
    // on a segment of voxels in that direction.  All voxels from first to
    // last are set to 1.  This is done for all segments in each of the
    // coordinate directions.
    static void ComputeCDConvex(Image3<int>& image);

    // Use a depth-first search for filling a 6-connected region.  This is
    // nonrecursive, simulated by using a heap-allocated "stack".  The input
    // (x,y,z) is the seed point that starts the fill.
    template <typename PixelType>
    static void FloodFill6(Image3<PixelType>& image, int x, int y, int z,
        PixelType foreColor, PixelType backColor);

    // Visit pixels using Bresenham's line drawing algorithm.  The callback
    // represents the action you want applied to each voxel as it is visited.
    static void DrawLine(int x0, int y0, int z0, int x1, int y1, int z1,
        std::function<void(int, int, int)> const& callback);

private:
    // Dilation using the specified structuring element.
    static void Dilate(int numNeighbors, std::array<int, 3> const* delta,
        Image3<int> const& inImage, Image3<int>& outImage);

    // Connected component labeling using depth-first search.
    static void GetComponents(int numNeighbors, int const* delta,
        Image3<int>& image, std::vector<std::vector<size_t>>& components);
};

#include "GteImageUtility3.inl"

}
