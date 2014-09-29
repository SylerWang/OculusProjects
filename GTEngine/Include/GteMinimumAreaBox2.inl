// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
MinimumAreaBox2<InputType, ComputeType>::MinimumAreaBox2()
    :
    mNumPoints(0),
    mPoints(nullptr)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumAreaBox2<InputType, ComputeType>::operator()(int numPoints,
    Vector2<InputType> const* points, InputType epsilon,
    OrientedBox2<InputType>& minBox)
{
    mNumPoints = numPoints;
    mPoints = points;

    // Get the convex hull of the points.
    ConvexHull2<InputType, ComputeType> ch;
    ch(mNumPoints, mPoints, epsilon);
    int dimension = ch.GetDimension();

    if (dimension == 0)
    {
        // The points are all effectively the same (using fuzzy epsilon).
        minBox.center = mPoints[0];
        minBox.axis[0] = Vector2<InputType>::Basis0();
        minBox.axis[1] = Vector2<InputType>::Basis1();
        minBox.extent[0] = (InputType)0;
        minBox.extent[1] = (InputType)0;
        mHull.resize(1);
        mHull[0] = 0;
        return true;
    }

    if (dimension == 1)
    {
        // The points effectively lie on a line (using fuzzy epsilon).
        // Determine the extreme t-values for the points represented as
        // P = origin + t*direction.  We know that 'origin' is an input
        // vertex, so we can start both t-extremes at zero.
        Line2<InputType> const& line = ch.GetLine();
        InputType tmin = (InputType)0, tmax = (InputType)0;
        int imin = 0, imax = 0;
        for (int i = 0; i < mNumPoints; ++i)
        {
            Vector2<InputType> diff = mPoints[i] - line.origin;
            InputType t = Dot(diff, line.direction);
            if (t > tmax)
            {
                tmax = t;
                imax = i;
            }
            else if (t < tmin)
            {
                tmin = t;
                imin = i;
            }
        }

        minBox.center = line.origin +
            ((InputType)0.5)*(tmin + tmax) * line.direction;
        minBox.extent[0] = ((InputType)0.5)*(tmax - tmin);
        minBox.extent[1] = (InputType)0;
        minBox.axis[0] = line.direction;
        minBox.axis[1] = -Perp(line.direction);
        mHull.resize(2);
        mHull[0] = imin;
        mHull[1] = imax;
        return true;
    }

    mHull = ch.GetHull();
    Vector2<ComputeType> const* queryPoints = ch.GetQuery().GetVertices();
    std::vector<Vector2<ComputeType>> computePoints(mHull.size());
    for (size_t i = 0; i < mHull.size(); ++i)
    {
        computePoints[i] = queryPoints[mHull[i]];
    }

    Convert(ComputeBox(computePoints), computePoints, minBox);
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumAreaBox2<InputType, ComputeType>::operator()(int numPoints,
    Vector2<InputType> const* points, int numIndices, int const* indices,
    OrientedBox2<InputType>& minBox)
{
    mHull.clear();
    if (numPoints < 3 || !points || (indices && numIndices < 3))
    {
        return false;
    }

    if (indices)
    {
        mHull.resize(numIndices);
        std::copy(indices, indices + numIndices, mHull.begin());
    }
    else
    {
        numIndices = numPoints;
        mHull.resize(numIndices);
        for (int i = 0; i < numIndices; ++i)
        {
            mHull[i] = i;
        }
    }

    std::vector<Vector2<ComputeType>> computePoints(numIndices);
    for (int i = 0; i < numIndices; ++i)
    {
        int h = mHull[i];
        computePoints[i][0] = (ComputeType)points[h][0];
        computePoints[i][1] = (ComputeType)points[h][1];
    }

    Convert(ComputeBox(computePoints), computePoints, minBox);
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumAreaBox2<InputType, ComputeType>::DoOrderNSqr(int numPoints,
    Vector2<InputType> const* points, int numIndices, int const* indices,
    OrientedBox2<InputType>& minBox)
{
    mHull.clear();
    if (numPoints < 3 || !points || (indices && numIndices < 3))
    {
        return false;
    }

    if (indices)
    {
        mHull.resize(numIndices);
        std::copy(indices, indices + numIndices, mHull.begin());
    }
    else
    {
        numIndices = numPoints;
        mHull.resize(numIndices);
        for (int i = 0; i < numIndices; ++i)
        {
            mHull[i] = i;
        }
    }

    InputType minArea = std::numeric_limits<InputType>::max();
    std::vector<InputType> proj0(numIndices), proj1(numIndices);
    InputType const half = (InputType)0.5;
    for (int i0 = numIndices - 1, i1 = 0; i1 < numIndices; i0 = i1++)
    {
        Vector2<InputType> U0 = points[mHull[i1]] - points[mHull[i0]];
        Normalize(U0);
        Vector2<InputType> U1 = -Perp(U0);
        for (int j = 0; j < numIndices; ++j)
        {
            proj0[j] = Dot(U0, points[mHull[j]]);
            proj1[j] = Dot(U1, points[mHull[j]]);
        }
        auto result0 = std::minmax_element(proj0.begin(), proj0.end());
        auto result1 = std::minmax_element(proj1.begin(), proj1.end());
        InputType length0 = *result0.second - *result0.first;
        InputType length1 = *result1.second - *result1.first;
        InputType area = length0 * length1;
        if (area < minArea)
        {
            minArea = area;
            minBox.axis[0] = U0;
            minBox.axis[1] = U1;
            minBox.extent[0] = half * length0;
            minBox.extent[1] = half * length1;
            minBox.center =
                half * (*result0.first + *result0.second) * U0 +
                half * (*result1.first + *result1.second) * U1;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int MinimumAreaBox2<InputType, ComputeType>::GetNumPoints() const
{
    return mNumPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector2<InputType> const* MinimumAreaBox2<InputType, ComputeType>::GetPoints()
    const
{
    return mPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const&
MinimumAreaBox2<InputType, ComputeType>::GetHull() const
{
    return mHull;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
typename MinimumAreaBox2<InputType, ComputeType>::Box
MinimumAreaBox2<InputType, ComputeType>::ComputeBox(
std::vector<Vector2<ComputeType>> const& vertices)
{
    // The inputs are assumed to be the vertices of a convex polygon that
    // is counterclockwise ordered.  The input points must not contain three
    // consecutive collinear points.

    // As box edges are visited (box edge coincident with a polygon edge), we
    // mark them as visited to help terminate the algorithm accordingly.
    int numVertices = static_cast<int>(vertices.size());
    std::vector<bool> visited(numVertices);
    std::fill(visited.begin(), visited.end(), false);

    // The starting candidate for the minimum-area box is the axis-aligned
    // box of the input points.  When updating the extremes, we want the
    // bottom-most point on the left edge, the top-most point on the right
    // edge, the left-most point on the top edge, and the right-most point
    // on the bottom edge.  The polygon edges starting at these points are
    // then guaranteed to not to coincide with a box edge except when an
    // extreme point is shared by two box edges (at a corner).
    Box minBox;
    minBox.U[0] = Vector2<ComputeType>::Basis0();
    minBox.U[1] = Vector2<ComputeType>::Basis1();
    minBox.index[EXT_B] = 0;
    minBox.index[EXT_R] = 0;
    minBox.index[EXT_T] = 0;
    minBox.index[EXT_L] = 0;

    Vector2<ComputeType> support[4];
    support[EXT_B] = vertices[0];
    support[EXT_R] = vertices[0];
    support[EXT_T] = vertices[0];
    support[EXT_L] = vertices[0];

    for (int i = 1; i < numVertices; ++i)
    {
        Vector2<ComputeType> const& v = vertices[i];

        if (v[0] < support[EXT_L][0] ||
            (v[0] == support[EXT_L][0] && v[1] < support[EXT_L][1]))
        {
            // New left minimum OR same left minimum but closer to bottom.
            minBox.index[EXT_L] = i;
            support[EXT_L] = v;
        }

        if (v[0] > support[EXT_R][0] ||
            (v[0] == support[EXT_R][0] && v[1] > support[EXT_R][1]))
        {
            // New right maximum OR same right maximum but closer to top.
            minBox.index[EXT_R] = i;
            support[EXT_R] = v;
        }

        if (v[1] < support[EXT_B][1] ||
            (v[1] == support[EXT_B][1] && v[0] > support[EXT_B][0]))
        {
            // New bottom minimum OR same bottom minimum but closer to right.
            minBox.index[EXT_B] = i;
            support[EXT_B] = v;
        }

        if (v[1] > support[EXT_T][1] ||
            (v[1] == support[EXT_T][1] && v[0] < support[EXT_T][0]))
        {
            // New top maximum OR same top maximum but closer to left.
            minBox.index[EXT_T] = i;
            support[EXT_T] = v;
        }
    }

    minBox.area =
        (support[EXT_R][0] - support[EXT_L][0]) *
        (support[EXT_T][1] - support[EXT_B][1]);

    // Execute the rotating calipers algorithm.
    ComputeType const zero = (ComputeType)0;
    Vector2<ComputeType> tmp[2];
    Box box = minBox;
    for (;;)
    {
        // Determine the edge that forms the smallest angle with the current
        // box edges.  To support exact arithmetic in the algorithm, the box
        // axes are not normalized to be unit length.  However, both axes are
        // guaranteed to be the same length, so the algorithm is still based
        // on computing the maximum dot product.  The initial choice for Emax
        // was (0,0), but in a release build the compiler warns about a
        // potential division by zero in IsLarger.  The new choice still leads
        // to an initial Dot(Dmax,Emax) == 0 and gets the comparison chain
        // started.
        int flag = -1;
        Vector2<ComputeType> Dmax = box.U[0];
        Vector2<ComputeType> Emax = -Perp(Dmax);
        Vector2<ComputeType> Dcnd, Ecnd;
        int k0, k1;

        // Process the extreme on the bottom edge.
        k0 = box.index[EXT_B];
        k1 = k0 + 1;
        if (k1 == numVertices)
        {
            k1 = 0;
        }
        Dcnd = box.U[0];
        Ecnd = vertices[k1] - vertices[k0];
        if (IsLarger(Dcnd, Ecnd, Dmax, Emax))
        {
            Dmax = Dcnd;
            Emax = Ecnd;
            flag = EXT_B;
        }

        // Process the extreme on the right edge.
        k0 = box.index[EXT_R];
        k1 = k0 + 1;
        if (k1 == numVertices)
        {
            k1 = 0;
        }
        Dcnd = box.U[1];
        Ecnd = vertices[k1] - vertices[k0];
        if (IsLarger(Dcnd, Ecnd, Dmax, Emax))
        {
            Dmax = Dcnd;
            Emax = Ecnd;
            flag = EXT_R;
        }

        // Process the extreme on the top edge.
        k0 = box.index[EXT_T];
        k1 = k0 + 1;
        if (k1 == numVertices)
        {
            k1 = 0;
        }
        Dcnd = -box.U[0];
        Ecnd = vertices[k1] - vertices[k0];
        if (IsLarger(Dcnd, Ecnd, Dmax, Emax))
        {
            Dmax = Dcnd;
            Emax = Ecnd;
            flag = EXT_T;
        }

        // Process the extreme on the left edge.
        k0 = box.index[EXT_L];
        k1 = k0 + 1;
        if (k1 == numVertices)
        {
            k1 = 0;
        }
        Dcnd = -box.U[1];
        Ecnd = vertices[k1] - vertices[k0];
        if (IsLarger(Dcnd, Ecnd, Dmax, Emax))
        {
            Dmax = Dcnd;
            Emax = Ecnd;
            flag = EXT_L;
        }

        if (flag == -1 || visited[box.index[flag]])
        {
            // The polygon is a box OR we have already visited this edge.  In
            // either case, the search is over.
            break;
        }

        // Rotate the box and compute the area.
        box.U[0] = Emax;
        box.U[1] = -Perp(Emax);

        // Update the supporting points for the rotated box.  The current
        // supporting points remain supporting points for the rotated box, but
        // it is possible that a polygon edge starting at a supporting point
        // becomes coincident with a box edge (so two polygon edges are
        // parallel to a box axis).  The code chooses the correct endpoint of
        // a coincident edge to maintain the loop invariant that allows us to
        // compute the minimal angle of rotation for the next step.  TODO: The
        // code assumes that no three vertices are collinear.  Allow this; the
        // single test of DotPerp is replaced by a loop of tests.
        visited[box.index[flag]] = true;
        std::array<int, 4> newIndex;
        for (int i0 = 3, i1 = 0; i1 < 4; i0 = i1++)
        {
            if (box.index[i0] != box.index[i1])
            {
                k0 = box.index[i0];
                k1 = k0 + 1;
                if (k1 == numVertices)
                {
                    k1 = 0;
                }
                Ecnd = vertices[k1] - vertices[k0];
                newIndex[i0] = (DotPerp(Ecnd, Emax) != zero ? k0 : k1);
            }
            else
            {
                newIndex[i0] = box.index[i0];
            }
        }

        // Rename the edges so that the 'flag' edge becomes the new EXT_B
        // edge and the others are labeled accordingly in succession.
        for (int i = 0; i < 4; ++i)
        {
            box.index[i] = newIndex[(i + flag) % 4];
        }

        // Update the minimum-area box if necessary.
        tmp[0] = vertices[box.index[EXT_R]] - vertices[box.index[EXT_L]];
        tmp[1] = vertices[box.index[EXT_T]] - vertices[box.index[EXT_B]];
        box.area = Dot(box.U[0], tmp[0]) * Dot(box.U[1], tmp[1])
            / Dot(Emax, Emax);
        if (box.area < minBox.area)
        {
            minBox = box;
        }
    }

    return minBox;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
bool MinimumAreaBox2<InputType, ComputeType>::IsLarger(
    Vector2<ComputeType> const& D0,
    Vector2<ComputeType> const& E0,
    Vector2<ComputeType> const& D1,
    Vector2<ComputeType> const& E1)
{
    ComputeType const zero = (ComputeType)0;
    ComputeType d0e0 = Dot(D0, E0);
    ComputeType d1e1 = Dot(D1, E1);
    ComputeType e0e0 = Dot(E0, E0);
    ComputeType e1e1 = Dot(E1, E1);
    ComputeType tmp0, tmp1;

    if (d0e0 > zero)
    {
        if (d1e1 <= zero)
        {
            return true;
        }

        tmp0 = d0e0 * (d0e0 / e0e0);
        tmp1 = d1e1 * (d1e1 / e1e1);
        return tmp0 > tmp1;
    }

    if (d0e0 < zero)
    {
        if (d1e1 >= zero)
        {
            return false;
        }

        tmp0 = d0e0 * (d0e0 / e0e0);
        tmp1 = d1e1 * (d1e1 / e1e1);
        return tmp0 < tmp1;
    }

    return d1e1 < zero;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumAreaBox2<InputType, ComputeType>::Convert(Box const& minBox,
    std::vector<Vector2<ComputeType>> const& computePoints,
    OrientedBox2<InputType>& itMinBox)
{
    ComputeType sqrLength = Dot(minBox.U[0], minBox.U[0]);
    Vector2<ComputeType> tmp[2];
    tmp[0] =
        computePoints[minBox.index[EXT_R]] +
        computePoints[minBox.index[EXT_L]];
    tmp[1] =
        computePoints[minBox.index[EXT_T]] +
        computePoints[minBox.index[EXT_B]];
    Vector2<ComputeType> twoCenter = (
        Dot(minBox.U[0], tmp[0]) * minBox.U[0] +
        Dot(minBox.U[1], tmp[1]) * minBox.U[1]) / sqrLength;

    tmp[0] =
        computePoints[minBox.index[EXT_R]] -
        computePoints[minBox.index[EXT_L]];
    tmp[1] =
        computePoints[minBox.index[EXT_T]] -
        computePoints[minBox.index[EXT_B]];
    Vector2<ComputeType> twoExtent(
        Dot(minBox.U[0], tmp[0]),
        Dot(minBox.U[1], tmp[1]));

    InputType const half = (InputType)0.5;
    InputType const invLength = ((InputType)1) / sqrt((InputType)sqrLength);
    for (int i = 0; i < 2; ++i)
    {
        itMinBox.center[i] = half * (InputType)twoCenter[i];
        itMinBox.extent[i] = half * invLength * (InputType)twoExtent[i];
        for (int j = 0; j < 2; ++j)
        {
            itMinBox.axis[i][j] = (InputType)minBox.U[i][j];
        }
        Normalize(itMinBox.axis[i]);
    }
}
//----------------------------------------------------------------------------
