// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline size_t AMDPerformance::GetNumProfileCalls() const
{
    return mNumProfileCalls;
}
//----------------------------------------------------------------------------
inline gpa_uint32 AMDPerformance::GetMaxCounters() const
{
    return mMaxCounters;
}
//----------------------------------------------------------------------------
inline std::string AMDPerformance::GetName(unsigned int counter) const
{
    return (counter < mMaxCounters ? mNames[counter] : "");
}
//----------------------------------------------------------------------------
inline std::string AMDPerformance::GetDescription(unsigned int counter) const
{
    return (counter < mMaxCounters ? mDescriptions[counter] : "");
}
//----------------------------------------------------------------------------
inline GPA_Type AMDPerformance::GetDataType(unsigned int counter) const
{
    return (counter < mMaxCounters ? mDataTypes[counter] : GPA_TYPE__LAST);
}
//----------------------------------------------------------------------------
inline GPA_Usage_Type AMDPerformance::GetAccess(unsigned int counter) const
{
    return (counter < mMaxCounters ? mUsageTypes[counter]
        : GPA_USAGE_TYPE__LAST);
}
//----------------------------------------------------------------------------
