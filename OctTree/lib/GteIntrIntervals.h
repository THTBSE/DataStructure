// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include <array>
#include <limits>

namespace gte
{

// The intervals are [u0,u1] and [v0,v1], where u0 <= u1 and v0 <= v1, and
// where the endpoints are any finite floating-point numbers.  Degenerate
// intervals are allowed (u0 = u1 or v0 = v1).  The queries do not perform
// validation on the input intervals.  In the comments, maxReal refers to
// std::numeric_limits<Real>::max().

template <typename Real>
class TIQuery<Real, std::array<Real,2>, std::array<Real,2>>
{
public:
    // The query tests overlap, whether a single point or an entire interval.
    struct Result
    {
        bool intersect;

        // Dynamic queries (intervals moving with constant speeds).  If
        // 'intersect' is true, the contact times are valid and
        //     0 <= firstTime <= lastTime,  firstTime <= maxTime
        // If 'intersect' is false, there are two cases reported.  If the
        // intervals will intersect at firstTime > maxTime, the contact times
        // are reported just as when 'intersect' is true.  However, if the
        // intervals will not intersect, then firstTime = maxReal and
        // lastTime = -maxReal.
        Real firstTime, lastTime;
    };

    // Static query.
    Result operator()(std::array<Real, 2> const& interval0,
        std::array<Real, 2> const& interval1);

    // Dynamic query.  Current time is 0, maxTime > 0 is required.
    Result operator()(Real maxTime, std::array<Real, 2> const& interval0,
        Real speed0, std::array<Real, 2> const& interval1, Real speed1);
};

template <typename Real>
class FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>
{
public:
    // The query finds overlap, whether a single point or an entire interval.
    struct Result
    {
        bool intersect;

        // Static queries (no motion of intervals over time).  The number of
        // number of intersections is 0 (no overlap), 1 (intervals are just
        // touching), or 2 (intervals overlap in an interval).  If 'intersect'
        // is false, numIntersections is 0 and 'overlap' is set to
        // [maxReal,-maxReal].  If 'intersect' is true, numIntersections is
        // 1 or 2.  When 1, 'overlap' is set to [x,x], which is degenerate and
        // represents the single intersection point x.  When 2, 'overlap' is
        // the interval of intersection.
        int numIntersections;
        std::array<Real, 2> overlap;

        // Dynamic queries (intervals moving with constant speeds).  If
        // 'intersect' is true, the contact times are valid and
        //     0 <= firstTime <= lastTime,  firstTime <= maxTime
        // If 'intersect' is false, there are two cases reported.  If the
        // intervals will intersect at firstTime > maxTime, the contact times
        // are reported just as when 'intersect' is true.  However, if the
        // intervals will not intersect, then firstTime = maxReal and
        // lastTime = -maxReal.
        Real firstTime, lastTime;
    };

    // Static query.
    Result operator()(std::array<Real, 2> const& interval0,
        std::array<Real, 2> const& interval1);

    // Dynamic query.  Current time is 0, maxTime > 0 is required.
    Result operator()(Real maxTime, std::array<Real, 2> const& interval0,
        Real speed0, std::array<Real, 2> const& interval1, Real speed1);
};

#include "GteIntrIntervals.inl"

}
