// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class FitExp2
{
public:
    FitExp2();

    template <int Degree>
    void Generate(std::vector<double>& poly, double& error) const;

private:
    // f(x) = 2^x for x in [0,1].
    // g(x) = 2^x - p(x)
    double G(double x, int const degree, double const* p) const;

    // g'(x) = 2^x*log(2) - p'(x)
    double GDer(double x, int const degree, double const* p) const;

    int SignG(double x, int const degree, double const* p) const;
    int SignGDer(double x, int const degree, double const* p) const;
};

#include "FitExp2.inl"
