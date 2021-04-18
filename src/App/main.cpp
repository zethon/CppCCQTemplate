#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
 
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
 
    QWidget widget;
    widget.resize(640, 480);
    widget.setWindowTitle("Hello, world!!!");
    
    QGridLayout *gridLayout = new QGridLayout(&widget);
 
    QLabel * label = new QLabel("Hello, world!!!");
    label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(label);
 
    widget.show();
 
    return app.exec();
}
