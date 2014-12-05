// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::Result
TIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::operator()(
    std::array<Real, 2> const& interval0,
    std::array<Real, 2> const& interval1)
{
    Result result;
    result.intersect =
        interval0[0] <= interval1[1] && interval0[1] >= interval1[0];
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, std::array<Real,2>, std::array<Real,2>>::Result
TIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::operator()(
    Real maxTime, std::array<Real, 2> const& interval0, Real speed0,
    std::array<Real, 2> const& interval1, Real speed1)
{
    Result result;

    if (interval0[1] < interval1[0])
    {
        // interval0 initially to the left of interval1.
        Real diffSpeed = speed0 - speed1;
        if (diffSpeed > (Real)0)
        {
            // The intervals must move towards each other.  'intersect' is
            // true when the intervals will intersect by maxTime.
            Real diffPos = interval1[0] - interval0[1];
            Real invDiffSpeed = ((Real)1) / diffSpeed;
            result.intersect = (diffPos <= maxTime*diffSpeed);
            result.firstTime = diffPos*invDiffSpeed;
            result.lastTime = (interval1[1] - interval0[0])*invDiffSpeed;
            return result;
        }
    }
    else if (interval0[0] > interval1[1])
    {
        // interval0 initially to the right of interval1.
        Real diffSpeed = speed1 - speed0;
        if (diffSpeed > (Real)0)
        {
            // The intervals must move towards each other.  'intersect' is
            // true when the intervals will intersect by maxTime.
            Real diffPos = interval0[0] - interval1[1];
            Real invDiffSpeed = ((Real)1) / diffSpeed;
            result.intersect = (diffPos <= maxTime*diffSpeed);
            result.firstTime = diffPos*invDiffSpeed;
            result.lastTime = (interval0[1] - interval1[0])*invDiffSpeed;
            return result;
        }
    }
    else
    {
        // The intervals are initially intersecting.
        result.intersect = true;
        result.firstTime = (Real)0;
        if (speed1 > speed0)
        {
            result.lastTime = (interval0[1] - interval1[0])/(speed1 - speed0);
        }
        else if (speed1 < speed0)
        {
            result.lastTime = (interval1[1] - interval0[0])/(speed0 - speed1);
        }
        else
        {
            result.lastTime = std::numeric_limits<Real>::max();
        }
        return result;
    }

    result.intersect = false;
    result.firstTime = std::numeric_limits<Real>::max();
    result.lastTime = -std::numeric_limits<Real>::max();
    return result;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::Result
FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::operator()(
    std::array<Real, 2> const& interval0,
    std::array<Real, 2> const& interval1)
{
    Result result;
    result.firstTime = std::numeric_limits<Real>::max();
    result.lastTime = -std::numeric_limits<Real>::max();

    if (interval0[1] < interval1[0] || interval0[0] > interval1[1])
    {
        result.numIntersections = 0;
        result.overlap[0] = std::numeric_limits<Real>::max();
        result.overlap[1] = -std::numeric_limits<Real>::max();
    }
    else if (interval0[1] > interval1[0])
    {
        if (interval0[0] < interval1[1])
        {
            result.numIntersections = 2;
            result.overlap[0] = 
                (interval0[0] < interval1[0] ? interval1[0] : interval0[0]);
            result.overlap[1] =
                (interval0[1] > interval1[1] ? interval1[1] : interval0[1]);
            if (result.overlap[0] == result.overlap[1])
            {
                result.numIntersections = 1;
            }
        }
        else  // interval0[0] == interval1[1]
        {
            result.numIntersections = 1;
            result.overlap[0] = interval0[0];
            result.overlap[1] = result.overlap[0];
        }
    }
    else  // interval0[1] == interval1[0]
    {
        result.numIntersections = 1;
        result.overlap[0] = interval0[1];
        result.overlap[1] = result.overlap[0];
    }

    result.intersect = (result.numIntersections > 0);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::Result
FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>>::operator()(
    Real maxTime, std::array<Real, 2> const& interval0, Real speed0,
    std::array<Real, 2> const& interval1, Real speed1)
{
    Result result;

    if (interval0[1] < interval1[0])
    {
        // interval0 initially to the left of interval1.
        Real diffSpeed = speed0 - speed1;
        if (diffSpeed > (Real)0)
        {
            // The intervals must move towards each other.  'intersect' is
            // true when the intervals will intersect by maxTime.
            Real diffPos = interval1[0] - interval0[1];
            Real invDiffSpeed = ((Real)1) / diffSpeed;
            result.intersect = (diffPos <= maxTime*diffSpeed);
            result.numIntersections = 1;
            result.firstTime = diffPos*invDiffSpeed;
            result.lastTime = (interval1[1] - interval0[0])*invDiffSpeed;
            result.overlap[0] = interval0[0] + result.firstTime*speed0;
            result.overlap[1] = result.overlap[0];
            return result;
        }
    }
    else if (interval0[0] > interval1[1])
    {
        // interval0 initially to the right of interval1.
        Real diffSpeed = speed1 - speed0;
        if (diffSpeed > (Real)0)
        {
            // The intervals must move towards each other.  'intersect' is
            // true when the intervals will intersect by maxTime.
            Real diffPos = interval0[0] - interval1[1];
            Real invDiffSpeed = ((Real)1) / diffSpeed;
            result.intersect = (diffPos <= maxTime*diffSpeed);
            result.numIntersections = 1;
            result.firstTime = diffPos*invDiffSpeed;
            result.lastTime = (interval0[1] - interval1[0])*invDiffSpeed;
            result.overlap[0] = interval1[1] + result.firstTime*speed1;
            result.overlap[1] = result.overlap[0];
            return result;
        }
    }
    else
    {
        // The intervals are initially intersecting.
        result.intersect = true;
        result.firstTime = (Real)0;
        if (speed1 > speed0)
        {
            result.lastTime = (interval0[1] - interval1[0])/(speed1 - speed0);
        }
        else if (speed1 < speed0)
        {
            result.lastTime = (interval1[1] - interval0[0])/(speed0 - speed1);
        }
        else
        {
            result.lastTime = std::numeric_limits<Real>::max();
        }

        if (interval0[1] > interval1[0])
        {
            if (interval0[0] < interval1[1])
            {
                result.numIntersections = 2;
                result.overlap[0] = (interval0[0] < interval1[0] ?
                    interval1[0] : interval0[0]);
                result.overlap[1] = (interval0[1] > interval1[1] ?
                    interval1[1] : interval0[1]);
            }
            else  // interval0[0] == interval1[1]
            {
                result.numIntersections = 1;
                result.overlap[0] = interval0[0];
                result.overlap[1] = result.overlap[0];
            }
        }
        else  // interval0[1] == interval1[0]
        {
            result.numIntersections = 1;
            result.overlap[0] = interval0[1];
            result.overlap[1] = result.overlap[0];
        }
        return result;
    }

    result.intersect = false;
    result.numIntersections = 0;
    result.overlap[0] = std::numeric_limits<Real>::max();
    result.overlap[1] = -std::numeric_limits<Real>::max();
    result.firstTime = std::numeric_limits<Real>::max();
    result.lastTime = -std::numeric_limits<Real>::max();
    return result;
}
//----------------------------------------------------------------------------
