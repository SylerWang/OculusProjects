// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/25)

//----------------------------------------------------------------------------
template <typename PixelType>
void ImageUtility3::FloodFill6(Image3<PixelType>& image, int x, int y,
    int z, PixelType foreColor, PixelType backColor)
{
    // Test for a valid seed.
    int const dim0 = image.GetDimension(0);
    int const dim1 = image.GetDimension(1);
    int const dim2 = image.GetDimension(2);
    if (x < 0 || x >= dim0 || y < 0 || y >= dim1 || z < 0 || z >= dim2)
    {
        // The seed point is outside the image domain, so nothing to fill.
        return;
    }

    // Allocate the maximum amount of space needed for the stack.  An empty
    // stack has top == -1.
    size_t const numPixels = image.GetNumPixels();
    int* xStack = new int[numPixels];
    int* yStack = new int[numPixels];
    int* zStack = new int[numPixels];

    // Push seed point onto stack if it has the background color.  All points
    // pushed onto stack have background color backColor.
    int top = 0;
    xStack[top] = x;
    yStack[top] = y;
    zStack[top] = z;

    while (top >= 0)  // stack is not empty
    {
        // Read top of stack.  Do not pop since we need to return to this
        // top value later to restart the fill in a different direction.
        x = xStack[top];
        y = yStack[top];
        z = zStack[top];

        // Fill the pixel.
        image(x, y, z) = foreColor;

        int xp1 = x + 1;
        if (xp1 < dim0 && image(xp1, y, z) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = xp1;
            yStack[top] = y;
            zStack[top] = z;
            continue;
        }

        int xm1 = x - 1;
        if (0 <= xm1 && image(xm1, y, z) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = xm1;
            yStack[top] = y;
            zStack[top] = z;
            continue;
        }

        int yp1 = y + 1;
        if (yp1 < dim1 && image(x, yp1, z) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = yp1;
            zStack[top] = z;
            continue;
        }

        int ym1 = y - 1;
        if (0 <= ym1 && image(x, ym1, z) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = ym1;
            zStack[top] = z;
            continue;
        }

        int zp1 = z + 1;
        if (zp1 < dim2 && image(x, y, zp1) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = y;
            zStack[top] = zp1;
            continue;
        }

        int zm1 = z - 1;
        if (0 <= zm1 && image(x, y, zm1) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = y;
            zStack[top] = zm1;
            continue;
        }

        // Done in all directions, pop and return to search other directions.
        --top;
    }

    delete[] xStack;
    delete[] yStack;
    delete[] zStack;
}
//----------------------------------------------------------------------------
