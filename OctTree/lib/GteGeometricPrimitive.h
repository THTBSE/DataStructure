// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/10/25)

#pragma once

#include "GTEngineDEF.h"

namespace gte
{

template <typename T>
class GeometricPrimitive
{
public:
    // Comparisons for sorted containers and geometric ordering.  These use
    // the Curiously Recurring Template Pattern.  This avoids having a
    // virtual function table pointer, which in turn allows typecasting of
    // non-GTE primitives to GTE primitives when using GTE as a third-party
    // package.  Derived classes must implement the public comparisons:
    //    bool IsEqualTo(PrimitiveClass const& object) const;
    //    bool IsLessThan(PrimitiveClass const& object) const;
    // where PrimitiveClass is the class name for the geometric primitive;
    // for example, AlignedBox3.

    bool operator==(T const& object) const;
    bool operator!=(T const& object) const;
    bool operator< (T const& object) const;
    bool operator<=(T const& object) const;
    bool operator> (T const& object) const;
    bool operator>=(T const& object) const;
};

#include "GteGeometricPrimitive.inl"

}
