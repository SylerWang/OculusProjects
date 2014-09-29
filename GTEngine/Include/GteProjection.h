// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteEllipse2.h"
#include "GteEllipsoid3.h"
#include "GteLine2.h"
#include "GteLine3.h"

namespace gte
{

// Project an ellipse onto a line.  The projection interval is [smin,smax]
// and corresponds to the line segment P+s*D, where smin <= s <= smax.
template <typename Real>
void Project(Ellipse2<Real> const& ellipse, Line2<Real> const& line,
    Real& smin, Real& smax);

// Project an ellipsoid onto a line.  The projection interval is [smin,smax]
// and corresponds to the line segment P+s*D, where smin <= s <= smax.
template <typename Real>
void Project(Ellipsoid3<Real> const& ellipsoid,
    Line3<Real> const& line, Real& smin, Real& smax);

#include "GteProjection.inl"

}
