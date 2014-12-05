// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteVector3.h"

namespace gte
{

// The segment is represented by (1-s)*P0+s*P1, where P0 and P1 are the
// endpoints of the segment and 0 <= s <= 1.  Some algorithms prefer a
// centered representation that is similar to how oriented bounding boxes are
// defined.  This representation is C+t*D, where C = (P0+P1)/2 is the center
// of the segment, D = (P1-P0)/Length(P1-P0) is a unit-length direction vector
// for the segment, and |t| <= e.  The value e = Length(P1-P0)/2 is the extent
// (or radius or half-length) of the segment.

template <typename Real>
class Segment3 : public GeometricPrimitive<Segment3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets p0 to
    // (-1,0,0) and p1 to (1,0,0).  The last constructor computes
    // p0 = center - extent*direction and p1 = center + extent*direction.
    Segment3();
    Segment3(Vector3<Real> const& inP0, Vector3<Real> const& inP1);
    Segment3(Vector3<Real> const& center, Vector3<Real> const& direction,
        Real extent);

    // Compute the centered representation.  NOTE:  If you set p0 and p1;
    // compute C, D, and e; and then recompute q0 = C-e*D and q1 = C+e*D,
    // numerical round-off errors can lead to q0 not exactly equal to p0
    // and q1 not exactly equal to p1.
    void GetCenteredForm(Vector3<Real>& center, Vector3<Real>& direction,
        Real& extent) const;

    // Public member access.
    Vector3<Real> p[2];

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Segment3 const& segment) const;
    bool IsLessThan(Segment3 const& segment) const;
};

#include "GteSegment3.inl"

}
