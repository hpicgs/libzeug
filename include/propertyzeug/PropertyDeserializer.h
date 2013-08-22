
#pragma once

#include <regex>
#include <sstream>
#include <fstream>
#include "AbstractPropertyVisitor.h"

namespace propertyzeug {
    
class PROPERTYZEUG_API PropertySerializer : public AbstractPropertyVisitor
{
public:
    PropertySerializer();
    virtual ~PropertySerializer();

    virtual void visit(Property<bool> & property);
    virtual void visit(Property<int> & property);
    virtual void visit(Property<unsigned int> & property);
    virtual void visit(Property<long> & property);
    virtual void visit(Property<unsigned long> & property);
    virtual void visit(Property<char> & property);
    virtual void visit(Property<unsigned char> & property);
    virtual void visit(Property<float> & property);
    virtual void visit(Property<double> & property);
    virtual void visit(Property<std::string> & property);
    virtual void visit(Property<Color> & property);
    virtual void visit(Property<FilePath> & property);

    virtual void visit(PropertyGroup & property);

    bool deserialize(PropertyGroup & group, std::string filePath);
    
protected:
    template <typename Type>
    Type convertString(const std::string & value);
    
    bool isGroupDeclaration(const std::string line);
    bool isPropertyDeclaration(const std::string line);
    
    bool updateCurrentGroup(const std::string line);
    bool setPropertyValue(const std::string line);
    
    std::fstream m_fstream;
    PropertyGroup * m_rootGroup;
    PropertyGroup * m_currentGroup;
    std::string m_currentValue;
};
    
template <typename Type>
Type PropertySerializer::convertString(const std::string & stringValue)
{
    std::stringstream stream(stringValue);
    Type value;
    stream >> value;
    return value;
}

} // namespace