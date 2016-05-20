//!!! Qt5
//! Proram:
//!     A calculator
//! History:
//!     05/07/2015 v0.1.0,:Finish the simple Layout
//!     05/08/2015 v0.2.0:Realize the buttons' function except calculation button
//!     09/24/2015 v0.3.0:Realize the main function of the rest of button,can only calculate equation with +,-,*,/ without ();
//!     09/25/2015 v0.3.1:Fixed some bugs:
//!                       1.Operator button is enable when delete a equation that is calculated before delete '='
//!                       2.Divide is not work normolly
//!                       3.Number button and operator button append the charactor to the calculated equation.
//!     09/25/2015 v0.4.0:Realize the Ans button,move unnecessary '0' and '.'.
//!     14/05/2016 v1.0.0:添加复杂表达式的计算
//!                       TODO: 1.界面修改
//!                             2.键盘不响应无效按键

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
