// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class FitCos
{
public:
    FitCos();

    // The degree D = 2*Order.  The polynomial coefficients are for
    // the even powers of x.
    template <int Order>
    void Generate(std::vector<double>& poly, double& error) const;

private:
    // f(x) = cos(x)
    // g(x) = cos(x) - p(x)
    double G(double x, int const order, double const* p) const;

    // g'(x) = -sin(x) - p'(x)
    double GDer(double x, int const order, double const* p) const;

    int SignG(double x, int const order, double const* p) const;
    int SignGDer(double x, int const order, double const* p) const;
};

#include "FitCos.inl"
