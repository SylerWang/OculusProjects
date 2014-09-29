// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ray2<Real>, AlignedBox2<Real>>::Result
TIQuery<Real, Ray2<Real>, AlignedBox2<Real>>::operator()(
    Ray2<Real> const& ray, AlignedBox2<Real> const& box)
{
    // Get the centered form of the aligned box.  The axes are implicitly
    // Axis[d] = Vector2<Real>::Unit(d).
    Vector2<Real> boxCenter, boxExtent;
    box.GetCenteredForm(boxCenter, boxExtent);

    // Transform the ray to the aligned-box coordinate system.
    Vector2<Real> rayOrigin = ray.origin - boxCenter;

    Result result;
    DoQuery(boxExtent, rayOrigin, ray.direction, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void TIQuery<Real, Ray2<Real>, AlignedBox2<Real>>::DoQuery(
    Vector2<Real> const& rayOrigin, Vector2<Real> const& rayDirection,
    Vector2<Real> const& boxExtent, Result& result)
{
    for (int i = 0; i < 2; ++i)
    {
        if (std::abs(rayOrigin[i]) > boxExtent[i]
            && rayOrigin[i] * rayDirection[i] >= (Real)0)
        {
            result.intersect = false;
            return;
        }
    }

    TIQuery<Real, Line2<Real>, AlignedBox2<Real>>::DoQuery(rayOrigin,
        rayDirection, boxExtent, result);
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ray2<Real>, AlignedBox2<Real>>::Result
FIQuery<Real, Ray2<Real>, AlignedBox2<Real>>::operator()(
    Ray2<Real> const& ray, AlignedBox2<Real> const& box)
{
    // Get the centered form of the aligned box.  The axes are implicitly
    // Axis[d] = Vector2<Real>::Unit(d).
    Vector2<Real> boxCenter, boxExtent;
    box.GetCenteredForm(boxCenter, boxExtent);

    // Transform the ray to the aligned-box coordinate system.
    Vector2<Real> rayOrigin = ray.origin - boxCenter;

    Result result;
    DoQuery(rayOrigin, ray.direction, boxExtent, result);
    for (int i = 0; i < result.numIntersections; ++i)
    {
        result.point[i] = ray.origin + result.parameter[i] * ray.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Ray2<Real>, AlignedBox2<Real>>::DoQuery(
    Vector2<Real> const& rayOrigin, Vector2<Real> const& rayDirection,
    Vector2<Real> const& boxExtent, Result& result)
{
    FIQuery<Real, Line2<Real>, AlignedBox2<Real>>::DoQuery(rayOrigin,
        rayDirection, boxExtent, result);

    if (result.intersect)
    {
        // The line containing the ray intersects the box; the t-interval is
        // [t0,t1].  The ray intersects the box as long as [t0,t1] overlaps
        // the ray t-interval [0,+infinity).
        std::array<Real, 2> rayInterval =
            { (Real)0, std::numeric_limits<Real>::max() };
        FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>> iiQuery;
        result.parameter = iiQuery(result.parameter, rayInterval).overlap;
    }
}
//----------------------------------------------------------------------------
