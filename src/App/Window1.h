#pragma once
#include <QtGui>
#include "ui_Window1.h"

namespace Ui
{  
	class Window1;
}

namespace app
{

class Window1 : public QDialog, public Ui::Window1
{
    Q_OBJECT

public:
    Window1(QWidget *parent = nullptr);

};

} // namespace
