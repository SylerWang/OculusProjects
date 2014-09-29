// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/25)

//----------------------------------------------------------------------------
template <typename PixelType>
void ImageUtility2::FloodFill4 (Image2<PixelType>& image, int x, int y,
    PixelType foreColor, PixelType backColor)
{
    // Test for a valid seed.
    int const dim0 = image.GetDimension(0);
    int const dim1 = image.GetDimension(1);
    if (x < 0 || x >= dim0 || y < 0 || y >= dim1)
    {
        // The seed point is outside the image domain, so nothing to fill.
        return;
    }

    // Allocate the maximum amount of space needed for the stack.  An empty
    // stack has top == -1.
    size_t const numPixels = image.GetNumPixels();
    int* xStack = new int[numPixels];
    int* yStack = new int[numPixels];

    // Push seed point onto stack if it has the background color.  All points
    // pushed onto stack have background color backColor.
    int top = 0;
    xStack[top] = x;
    yStack[top] = y;

    while (top >= 0)  // stack is not empty
    {
        // Read top of stack.  Do not pop since we need to return to this
        // top value later to restart the fill in a different direction.
        x = xStack[top];
        y = yStack[top];

        // Fill the pixel.
        image(x, y) = foreColor;

        int xp1 = x + 1;
        if (xp1 < dim0 && image(xp1, y) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = xp1;
            yStack[top] = y;
            continue;
        }

        int xm1 = x - 1;
        if (0 <= xm1 && image(xm1, y) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = xm1;
            yStack[top] = y;
            continue;
        }

        int yp1 = y + 1;
        if (yp1 < dim1 && image(x, yp1) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = yp1;
            continue;
        }

        int ym1 = y - 1;
        if (0 <= ym1 && image(x, ym1) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = ym1;
            continue;
        }

        // Done in all directions, pop and return to search other directions.
        --top;
    }

    delete[] xStack;
    delete[] yStack;
}
//----------------------------------------------------------------------------
template <typename PixelType>
void ImageUtility2::DrawFloodFill4(int x, int y, int xSize, int ySize,
    PixelType foreColor, PixelType backColor,
    std::function<void(int, int, PixelType)> const& setCallback,
    std::function<PixelType(int, int)> const& getCallback)
{
    // Test for a valid seed.
    if (x < 0 || x >= xSize || y < 0 || y >= ySize)
    {
        // The seed point is outside the image domain, so nothing to fill.
        return;
    }

    // Allocate the maximum amount of space needed for the stack.  An empty
    // stack has top == -1.
    int const numPixels = xSize * ySize;
    std::vector<int> xStack(numPixels), yStack(numPixels);

    // Push seed point onto stack if it has the background color.  All points
    // pushed onto stack have background color backColor.
    int top = 0;
    xStack[top] = x;
    yStack[top] = y;

    while (top >= 0)  // stack is not empty
    {
        // Read top of stack.  Do not pop since we need to return to this
        // top value later to restart the fill in a different direction.
        x = xStack[top];
        y = yStack[top];

        // Fill the pixel.
        setCallback(x, y, foreColor);

        int xp1 = x + 1;
        if (xp1 < xSize && getCallback(xp1, y) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = xp1;
            yStack[top] = y;
            continue;
        }

        int xm1 = x - 1;
        if (0 <= xm1 && getCallback(xm1, y) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = xm1;
            yStack[top] = y;
            continue;
        }

        int yp1 = y + 1;
        if (yp1 < ySize && getCallback(x, yp1) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = yp1;
            continue;
        }

        int ym1 = y - 1;
        if (0 <= ym1 && getCallback(x, ym1) == backColor)
        {
            // Push pixel with background color.
            ++top;
            xStack[top] = x;
            yStack[top] = ym1;
            continue;
        }

        // Done in all directions, pop and return to search other directions.
        --top;
    }
}
//----------------------------------------------------------------------------
