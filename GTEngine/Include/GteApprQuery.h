// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <algorithm>
#include <random>
#include <vector>

// Class ApprQuery supports the RANSAC algorithm for fitting and uses the
// Curiously Recurring Template Pattern.  The ModelType must be a class or
// struct with the following interfaces:
//
//   // The minimum number of observations required to fit the model.
//   int ModelType::GetMinimumRequired() const;
//
//   // Compute the model error for the specified observation for the current
//   // model parameters.
//   Real Error(ObservationType const& observation) const;
//
//   // Estimate the model parameters for all observations specified by the
//   // indices.  The three Fit() functions of ApprQuery manipulate their
//   // inputs in order to pass them to ModelType::Fit().
//   ModelType::Fit(std::vector<ObservationType> const& observations,
//       std::vector<size_t> const& indices);

namespace gte
{

template <typename Real, typename ModelType, typename ObservationType>
class ApprQuery
{
public:
    // Estimate the model parameters for all observations.
    bool Fit(std::vector<ObservationType> const& observations);

    // Estimate the model parameters for a contiguous subset of observations.
    bool Fit(std::vector<ObservationType> const& observations,
        int const imin, int const imax);

    // Estimate the model parameters for the subset of observations specified
    // by the indices and the number of indices that is possibly smaller than
    // indices.size().
    bool Fit(std::vector<ObservationType> const& observations,
        std::vector<int> const& indices, int const numIndices);

    // Apply the RANdom SAmple Consensus algorithm for fitting a model to
    // observations.
    static bool RANSAC(
        ModelType& candidateModel,
        std::vector<ObservationType> const& observations,
        int const numRequiredForGoodFit, Real const maxErrorForGoodFit,
        int const numIterations, std::vector<int>& bestConsensus,
        ModelType& bestModel);
};

#include "GteApprQuery.inl"

}
