// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Segment3<Real>::Segment3()
{
    p[0] = -Vector3<Real>::Basis0();
    p[1] = Vector3<Real>::Basis0();
}
//----------------------------------------------------------------------------
template <typename Real>
Segment3<Real>::Segment3(Vector3<Real> const& inP0, Vector3<Real> const& inP1)
{
    p[0] = inP0;
    p[1] = inP1;
}
//----------------------------------------------------------------------------
template <typename Real>
Segment3<Real>::Segment3(Vector3<Real> const& center,
    Vector3<Real> const& direction, Real extent)
{
    p[0] = center - extent * direction;
    p[1] = center + extent * direction;
}
//----------------------------------------------------------------------------
template <typename Real>
void Segment3<Real>::GetCenteredForm(Vector3<Real>& center,
    Vector3<Real>& direction, Real& extent) const
{
    center = ((Real)0.5)*(p[0] + p[1]);
    direction = p[1] - p[0];
    extent = ((Real)0.5)*Normalize(direction);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Segment3<Real>::IsEqualTo(Segment3 const& segment) const
{
    return p[0] == segment.p[0] && p[1] == segment.p[1];
}
//----------------------------------------------------------------------------
template <typename Real>
bool Segment3<Real>::IsLessThan(Segment3 const& segment) const
{
    if (p[0] < segment.p[0])
    {
        return true;
    }

    if (p[0] > segment.p[0])
    {
        return false;
    }

    return p[1] < segment.p[1];
}
//----------------------------------------------------------------------------
