// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Line3<Real>, AlignedBox3<Real>>::Result
TIQuery<Real, Line3<Real>, AlignedBox3<Real>>::operator()(
    Line3<Real> const& line, AlignedBox3<Real> const& box)
{
    // Get the centered form of the aligned box.  The axes are implicitly
    // Axis[d] = Vector3<Real>::Unit(d).
    Vector3<Real> boxCenter, boxExtent;
    box.GetCenteredForm(boxCenter, boxExtent);

    // Transform the line to the aligned-box coordinate system.
    Vector3<Real> lineOrigin = line.origin - boxCenter;

    Result result;
    DoQuery(lineOrigin, line.direction, boxExtent, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void TIQuery<Real, Line3<Real>, AlignedBox3<Real>>::DoQuery(
    Vector3<Real> const& lineOrigin, Vector3<Real> const& lineDirection,
    Vector3<Real> const& boxExtent, Result& result)
{
    Vector3<Real> WxD = Cross(lineDirection, lineOrigin);
    Real absWdU[3] =
    {
        std::abs(lineDirection[0]),
        std::abs(lineDirection[1]),
        std::abs(lineDirection[2])
    };

    if (std::abs(WxD[0]) > boxExtent[1]*absWdU[2] + boxExtent[2]*absWdU[1])
    {
        result.intersect = false;
        return;
    }

    if (std::abs(WxD[1]) > boxExtent[0]*absWdU[2] + boxExtent[2]*absWdU[0])
    {
        result.intersect = false;
        return;
    }

    if (std::abs(WxD[2]) > boxExtent[0]*absWdU[1] + boxExtent[1]*absWdU[0])
    {
        result.intersect = false;
        return;
    }

    result.intersect = true;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line3<Real>, AlignedBox3<Real>>::Result
FIQuery<Real, Line3<Real>, AlignedBox3<Real>>::operator()(
    Line3<Real> const& line, AlignedBox3<Real> const& box)
{
    // Get the centered form of the aligned box.  The axes are implicitly
    // Axis[d] = Vector3<Real>::Unit(d).
    Vector3<Real> boxCenter, boxExtent;
    box.GetCenteredForm(boxCenter, boxExtent);

    // Transform the line to the aligned-box coordinate system.
    Vector3<Real> lineOrigin = line.origin - boxCenter;

    Result result;
    DoQuery(lineOrigin, line.direction, boxExtent, result);
    for (int i = 0; i < result.numPoints; ++i)
    {
        result.point[i] =
            line.origin + result.lineParameter[i] * line.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Line3<Real>, AlignedBox3<Real>>::DoQuery(
    Vector3<Real> const& lineOrigin, Vector3<Real> const& lineDirection,
    Vector3<Real> const& boxExtent, Result& result)
{
    // The line t-values are in the interval (-infinity,+infinity).  Clip the
    // line against all six planes of an aligned box in centered form.  The
    // result.numEndpoints is
    //   0, no intersection
    //   1, intersect in a single point (t0 is line parameter of point)
    //   2, intersect in a segment (line parameter interval is [t0,t1])
    Real t0 = -std::numeric_limits<Real>::max();
    Real t1 = std::numeric_limits<Real>::max();
    if (Clip(+lineDirection[0], -lineOrigin[0] - boxExtent[0], t0, t1) &&
        Clip(-lineDirection[0], +lineOrigin[0] - boxExtent[0], t0, t1) &&
        Clip(+lineDirection[1], -lineOrigin[1] - boxExtent[1], t0, t1) &&
        Clip(-lineDirection[1], +lineOrigin[1] - boxExtent[1], t0, t1) &&
        Clip(+lineDirection[2], -lineOrigin[2] - boxExtent[2], t0, t1) &&
        Clip(-lineDirection[2], +lineOrigin[2] - boxExtent[2], t0, t1))
    {
        result.intersect = true;
        if (t1 > t0)
        {
            result.numPoints = 2;
            result.lineParameter[0] = t0;
            result.lineParameter[1] = t1;
        }
        else
        {
            result.numPoints = 1;
            result.lineParameter[0] = t0;
            result.lineParameter[1] = t0;  // Used by derived classes.
        }
        return;
    }

    result.intersect = false;
    result.numPoints = 0;
}
//----------------------------------------------------------------------------
template <typename Real>
bool FIQuery<Real, Line3<Real>, AlignedBox3<Real>>::Clip(Real denom,
    Real numer, Real& t0, Real& t1)
{
    if (denom > (Real)0)
    {
        if (numer > denom*t1)
        {
            return false;
        }
        if (numer > denom*t0)
        {
            t0 = numer/denom;
        }
        return true;
    }
    else if (denom < (Real)0)
    {
        if (numer > denom*t0)
        {
            return false;
        }
        if (numer > denom*t1)
        {
            t1 = numer/denom;
        }
        return true;
    }
    else
    {
        return numer <= (Real)0;
    }
}
//----------------------------------------------------------------------------
