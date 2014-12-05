// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
AlignedBox3<Real>::AlignedBox3()
{
    for (int i = 0; i < 3; ++i)
    {
        min[i] = (Real)-1;
        max[i] = (Real)+1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
AlignedBox3<Real>::AlignedBox3(Real const inMin[3], Real const inMax[3])
{
    for (int i = 0; i < 3; ++i)
    {
        min[i] = inMin[i];
        max[i] = inMax[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
AlignedBox3<Real>::AlignedBox3(Real min0, Real min1, Real min2, Real max0,
    Real max1, Real max2)
{
    min[0] = min0;
    min[1] = min1;
    min[2] = min2;
    max[0] = max0;
    max[1] = max1;
    max[2] = max2;
}
//----------------------------------------------------------------------------
template <typename Real>
void AlignedBox3<Real>::GetCenteredForm(Vector3<Real>& center,
    Vector3<Real>& extent) const
{
    center[0] = ((Real)0.5)*(max[0] + min[0]);
    center[1] = ((Real)0.5)*(max[1] + min[1]);
    center[2] = ((Real)0.5)*(max[2] + min[2]);

    extent[0] = ((Real)0.5)*(max[0] - min[0]);
    extent[1] = ((Real)0.5)*(max[1] - min[1]);
    extent[2] = ((Real)0.5)*(max[2] - min[2]);
}
//----------------------------------------------------------------------------
template <typename Real>
bool AlignedBox3<Real>::IsEqualTo(AlignedBox3 const& box) const
{
    for (int i = 0; i < 3; ++i)
    {
        if (min[i] != box.min[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (max[i] != box.max[i])
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool AlignedBox3<Real>::IsLessThan(AlignedBox3 const& box) const
{
    for (int i = 0; i < 3; ++i)
    {
        if (min[i] < box.min[i])
        {
            return true;
        }
        if (min[i] > box.min[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (max[i] < box.max[i])
        {
            return true;
        }
        if (max[i] > box.max[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
