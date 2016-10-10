#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QMenuBar>
#include <QVector>
#include <QStack>
#include "Expression.h"
#include "metacharacter.h"
#include "pushbutton.h"

/*
 * 定义按钮上的显示字符
 */
const string SHIFT = "↑";
const string BACKSPACE = "←";
const string CLEAR = "C";
const string ANS = "Ans";
//按钮布局
const QVector<QVector<string>> BUTTONS{{SIN, COS, TAN, LG},
                                       {"", "", "", LEFT_BRACKET, RIGHT_BRACKET},
                                       {SEVEN, EIGHT, NINE, ADD, EXTRACT_ROOT},
                                       {FOUR, FIVE, SIX, MINUS, POW},
                                       {ONE, TWO, THREE, MULTIPLY, MOD_PERCENT},
                                       {DEGREE, ZERO, POINT, DIVIDE, FACTORIAL}};
//shift转换按钮对应表
const QMap<string, string> SHIFT_TABLE{{SIN, ARCSIN},
                                       {COS,ARCCOS},
                                       {TAN, ARCTAN},
                                       {LG, LN}};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString cal(QString s); //计算,传入表达式s,返回表达式值
    Expression *expression; //表达式计算对象
private:
    QWidget *CentralWidget;

    QGridLayout *buttonsLayout;
    QGridLayout *MainLayout;

    QVector<PushButton *> buttons;  //按钮集合
    QVector<PushButton *> functionKeyButtons;   //功能键集合

    QPushButton *functionKeyButtonBackspace;    //回退一个字符
    QPushButton *functionKeyButtonClear;    //清空
    QPushButton *functionKeyButtonAns;  //上次计算结果
    QPushButton *functionKeyButtonShift;    //shift按钮
    QPushButton *equalButton;   //等于按钮
    QLineEdit *inputText;   //表达式输入框
    QLabel *equalLabel; //等于号
    QLineEdit *resultText;  //计算结果显示框

    QStack<int> historySize;
    QString Ans = "0";  //保存上次计算结果
    bool isShifting = false;    //shift键按下状态标记
    bool calcFinished = true;   //计算已完成状态标记(与正在输入表达式状态对应)

    /*
     * 将表达式中特殊字符转换为规范的计算字符
     * 本程序转换规则有:
     * 显示字符 计算字符
     *    ×     *
     *    ÷     /
     *    √     #
     *    °     `
     */
    string transformStdExpression(QString expression);
private slots:
    void setInputText(PushButton *pushButton);  //按钮按下时设置输入框,参数为按钮指针
    void onEqualClicked();  //等于按钮按下
    void onBackspaceClicked();  //删除按钮按下
    void onClearClicked();  //清空按钮按下
    void onAnsClicked();    //上次计算结果按钮按下
    void onShiftClicked();  //shift按钮按下

};

#endif // MAINWINDOW_H
