
#pragma once


#include <reflectionzeug/new/TypedBase.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for floating point types
*/
template <typename T>
class TypedFloatingPoint : public TypedBase<T>
{
public:
    TypedFloatingPoint(Accessor<T> * accessor);
    virtual ~TypedFloatingPoint();

    virtual double toDouble() const;
    virtual bool fromDouble(double value);
};


} // namespace reflectionzeug


#include <reflectionzeug/new/TypedFloatingPoint.hpp>