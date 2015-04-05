
#pragma once


#include <iostream>
#include <reflectionzeug/new/TypedClass.h>


namespace reflectionzeug
{


template <typename T>
TypedClass<T>::TypedClass(Accessor<T> * accessor)
: TypedBase<T>(accessor)
{
}

template <typename T>
TypedClass<T>::~TypedClass()
{
}

template <typename T>
std::string TypedClass<T>::toString() const
{
    return this->getValue().toString();
}

template <typename T>
bool TypedClass<T>::fromString(const std::string & string)
{
    bool ok;
    T value = T::fromString(string, &ok);

    if (!ok) {
        std::cout << "Could not read from string." << std::endl;
        return false;
    }

    this->setValue(value);
    return true;
}


} // namespace reflectionzeug