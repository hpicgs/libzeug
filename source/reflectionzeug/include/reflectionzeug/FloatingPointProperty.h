
#pragma once

#include <reflectionzeug/NumberProperty.h>
#include <reflectionzeug/FloatingPointPropertyInterface.h>


namespace reflectionzeug
{

/**
 * \brief Provides the property implementation for floating point types.
 *
 * While adding a precision member, it also implements the 
 * FloatingPointPropertyInterface
 *
 * \ingroup property_hierarchy
 */
template <typename Type>
class FloatingPointProperty : public FloatingPointPropertyInterface, public NumberProperty<Type>
{
public:
    template <typename... Arguments>
    FloatingPointProperty(Arguments&&... args);
    
    virtual ~FloatingPointProperty() = 0;

    virtual void accept(AbstractPropertyVisitor * visitor);

    virtual double doubleMinimum() const;
    virtual bool hasMinimum() const;

    virtual double doubleMaximum() const;
    virtual bool hasMaximum() const;

    virtual bool hasRange() const;

    virtual double doubleStep() const;
    virtual bool hasStep() const;

    virtual unsigned int precision() const;
    void setPrecision(unsigned int precision);
    virtual bool hasPrecision() const;

    virtual double toDouble() const;
    virtual bool fromDouble(double value);

protected:
    virtual std::string matchRegex() const;

protected:
    unsigned int m_precision;

};

} // namespace reflectionzeug

#include "FloatingPointProperty.hpp"
