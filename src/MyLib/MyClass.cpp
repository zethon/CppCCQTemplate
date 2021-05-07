#include "MyClass.h"

namespace app
{

MyClass::MyClass(const QString& text)
    : _text{text}
{
}

QString MyClass::appendIt(const QString& extra) const
{
    return _text + " " + extra;
}

QString MyClass::text() const
{
    return _text;
}

}