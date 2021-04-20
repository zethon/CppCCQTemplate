#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

#include <../MyLib/MyClass.h>
 
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
 
    QWidget widget;
    widget.resize(640, 480);
    widget.setWindowTitle("Hello, world!!!");
    
    QGridLayout *gridLayout = new QGridLayout(&widget);

    app::MyClass obj("Hello");
    QLabel * label = new QLabel(obj.appendIt("library world!!"));

    label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(label);
 
    widget.show();
 
    return app.exec();
}
