
#pragma once


#include <reflectionzeug/new/TypedFloatingPoint.h>


namespace reflectionzeug
{


template <typename T>
TypedFloatingPoint<T>::TypedFloatingPoint(Accessor<T> * accessor)
: TypedBase<T>(accessor)
{
}

template <typename T>
TypedFloatingPoint<T>::~TypedFloatingPoint()
{
}

template <typename T>
double TypedFloatingPoint<T>::toDouble() const
{
    return static_cast<double>(this->getValue());
}

template <typename T>
bool TypedFloatingPoint<T>::fromDouble(double value)
{
    this->setValue(static_cast<T>(value));
    return true;
}


} // namespace reflectionzeug