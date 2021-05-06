#include <QtTest>
#include "../src/MyLib/MyClass.h"

class Foo : public QObject 
{
    Q_OBJECT

private slots:
    void test1();
};

void Foo::test1()
{
    app::MyClass myclass{"test"};
    QCOMPARE(myclass.appendIt("test"), "test test");
}

QTEST_APPLESS_MAIN(Foo)

#include "testmain.moc"
