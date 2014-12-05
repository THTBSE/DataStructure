// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Triangle3<Real>::Triangle3()
{
    v[0] = Vector3<Real>::Origin();
    v[1] = Vector3<Real>::Basis0();
    v[2] = Vector3<Real>::Basis1();
}
//----------------------------------------------------------------------------
template <typename Real>
Triangle3<Real>::Triangle3(Vector3<Real> const& v0, Vector3<Real> const& v1,
    Vector3<Real> const& v2)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}
//----------------------------------------------------------------------------
template <typename Real>
Triangle3<Real>::Triangle3(std::array<Vector3<Real>, 3> const& inV)
{
    v = inV;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Triangle3<Real>::IsEqualTo(Triangle3 const& triangle) const
{
    return v[0] == triangle.v[0]
        && v[1] == triangle.v[1]
        && v[2] == triangle.v[2];
}
//----------------------------------------------------------------------------
template <typename Real>
bool Triangle3<Real>::IsLessThan(Triangle3 const& triangle) const
{
    for (int i = 0; i < 3; ++i)
    {
        if (v[i] < triangle.v[i])
        {
            return true;
        }

        if (v[i] > triangle.v[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
