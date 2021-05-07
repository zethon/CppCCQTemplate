#pragma once
#include <QString>

namespace app
{

class MyClass
{
    QString _text;

public:
    explicit MyClass(const QString& text);

    QString appendIt(const QString& extra) const;
    QString text() const;
};

}