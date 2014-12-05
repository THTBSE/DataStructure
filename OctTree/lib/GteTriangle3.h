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

// The triangle is represented as an array of three vertices: V0, V1, and V2.

template <typename Real>
class Triangle3 : public GeometricPrimitive<Triangle3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the
    // vertices to (0,0,0), (1,0,0), and (0,1,0).
    Triangle3();
    Triangle3(Vector3<Real> const& v0, Vector3<Real> const& v1,
        Vector3<Real> const& v2);
    Triangle3(std::array<Vector3<Real>,3> const& inV);

    // Public member access.
    std::array<Vector3<Real>,3> v;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Triangle3 const& triangle) const;
    bool IsLessThan(Triangle3 const& triangle) const;
};

#include "GteTriangle3.inl"

}
