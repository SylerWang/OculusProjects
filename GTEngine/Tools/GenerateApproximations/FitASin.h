// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class FitASin
{
public:
    FitASin();

    template <int Degree>
    void Generate(std::vector<double>& poly, double& error) const;

private:
    // f(x) = (pi/2 - asin(x))/sqrt(1 - x)
    // lim_{x->1} f(x) = sqrt(2)
    double F(double x) const;

    // g(x) = f(x) - p(x)
    double G(double x, int const degree, double const* p) const;

    // (1-x)*f'(x) = -1/sqrt(1 + x) + f(x)/2
    // lim_{x->1 f'(x) = -pow(2,-1.5)/3
    double FDer(double x) const;

    // g'(x) = f'(x) - p'(x)
    double GDer(double x, int const degree, double const* p) const;

    int SignG(double x, int const degree, double const* p) const;
    int SignGDer(double x, int const degree, double const* p) const;
};

#include "FitASin.inl"
