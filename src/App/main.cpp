#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include <../MyLib/MyClass.h>
#include <../MyLib/MyQMLClass.h>
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

    QPushButton* btn1 = new QPushButton("UI File");
    QObject::connect(btn1, &QPushButton::released, &widget,
        []() 
        { 
            app::Window1* dialog = new app::Window1();
            dialog->setModal(true);
            dialog->setWindowModality(Qt::ApplicationModal);
            dialog->exec();
            delete dialog;
        });

    QPushButton* btn2 = new QPushButton("QML File");
    QObject::connect(btn2, &QPushButton::released, &widget,
        []()
        {
//            app::MyQMLWidget* myqml = new app::MyQMLWidget();
        });

    label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(label);
    gridLayout->addWidget(btn1);
    gridLayout->addWidget(btn2);
 
    widget.show();
 
    return app.exec();
}
