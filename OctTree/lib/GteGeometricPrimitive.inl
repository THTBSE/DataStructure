// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename T>
bool GeometricPrimitive<T>::operator==(T const& object) const
{
    return ((T const*)this)->IsEqualTo(object);
}
//----------------------------------------------------------------------------
template <typename T>
bool GeometricPrimitive<T>::operator!=(T const& object) const
{
    return !((T const*)this)->IsEqualTo(object);
}
//----------------------------------------------------------------------------
template <typename T>
bool GeometricPrimitive<T>::operator<(T const& object) const
{
    return ((T const*)this)->IsLessThan(object);
}
//----------------------------------------------------------------------------
template <typename T>
bool GeometricPrimitive<T>::operator<=(T const& object) const
{
    return ((T const*)this)->IsLessThan(object)
        || ((T const*)this)->IsEqualTo(object);
}
//----------------------------------------------------------------------------
template <typename T>
bool GeometricPrimitive<T>::operator>(T const& object) const
{
    return !((T const*)this)->IsLessThan(object)
        && !((T const*)this)->IsEqualTo(object);
}
//----------------------------------------------------------------------------
template <typename T>
bool GeometricPrimitive<T>::operator>=(T const& object) const
{
    return !((T const*)this)->IsLessThan(object);
}
//----------------------------------------------------------------------------
