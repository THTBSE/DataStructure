// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Line3<Real>::Line3()
    :
    origin(Vector3<Real>::Origin()),
    direction(Vector3<Real>::Basis0())
{
}
//----------------------------------------------------------------------------
template <typename Real>
Line3<Real>::Line3(Vector3<Real> const& inOrigin,
    Vector3<Real> const& inDirection)
    :
    origin(inOrigin),
    direction(inDirection)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Line3<Real>::IsEqualTo(Line3 const& line) const
{
    return origin == line.origin && direction == line.direction;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Line3<Real>::IsLessThan(Line3 const& line) const
{
    if (origin < line.origin)
    {
        return true;
    }

    if (origin > line.origin)
    {
        return false;
    }

    return direction < line.direction;
}
//----------------------------------------------------------------------------
