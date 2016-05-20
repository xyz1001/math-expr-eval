#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include "Expression.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setOperatorBtnEnable(bool ok);
    QString cal(QString s);
    Expression *expression;
private:
    QMenu *File;
    QWidget *CentralWidget;
    QGridLayout *NumberLayout;
    QVBoxLayout *MainLayout;
    QVBoxLayout *OperatorLayout;
    QVBoxLayout *FunctionKeyLayout;
    QHBoxLayout *ButtonLayout;
    QPushButton *NumberButton0;
    QPushButton *NumberButton1;
    QPushButton *NumberButton2;
    QPushButton *NumberButton3;
    QPushButton *NumberButton4;
    QPushButton *NumberButton5;
    QPushButton *NumberButton6;
    QPushButton *NumberButton7;
    QPushButton *NumberButton8;
    QPushButton *NumberButton9;
    QPushButton *OperatorButtonPoint;
    QPushButton *OperatorButtonEqual;
    QPushButton *OperatorButtonAdd;
    QPushButton *OperatorButtonSub;
    QPushButton *OperatorButtonMul;
    QPushButton *OperatorButtonDiv;
    QPushButton *FunctionKeyButtonDelete;
    QPushButton *FunctionKeyButtonCE;
    QPushButton *FunctionKeyButtonQuit;
    QPushButton *FunctionKeyButtonAns;
    QLineEdit *ResultText;

    QAction *Quit;

    QString Ans;

    bool isCalc;
private slots:
    void setResultText0();
    void setResultText1();
    void setResultText2();
    void setResultText3();
    void setResultText4();
    void setResultText5();
    void setResultText6();
    void setResultText7();
    void setResultText8();
    void setResultText9();
    void setResultTextPoint();
    void setResultTextEqual();
    void setResultTextAdd();
    void setResultTextSub();
    void setResultTextMul();
    void setResultTextDiv();
    void setResultTextDelete();
    void setResultTextCE();
    void setResultTextAns();
};

#endif // MAINWINDOW_H
