#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include <../MyLib/MyClass.h>
#include "Window1.h"
 
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
 
    QWidget widget;
    widget.resize(640, 480);
    widget.setWindowTitle("Hello, world!!!");
    
    QGridLayout *gridLayout = new QGridLayout(&widget);

    app::MyClass obj("Hello");
    QLabel* label = new QLabel(obj.appendIt("library world!!"));

    QPushButton* btn1 = new QPushButton("Push Me");
    QObject::connect(btn1, &QPushButton::released, &widget,
        []() 
        { 
            app::Window1* dialog = new app::Window1();
            dialog->setModal(true);
            dialog->setWindowModality(Qt::ApplicationModal);
            dialog->exec();
            delete dialog;
        });

    label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(label);
    gridLayout->addWidget(btn1);
 
    widget.show();
 
    return app.exec();
}
