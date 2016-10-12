/******************************************************************************
 * main.cpp - 计算器
 *
 * Copyright (c) 2015-2016  Zix
 *
 * DESCRIPTION: -
 *   支持计算数学表达式的计算器,界面通过Qt5实现
 *
 * Version：0.1
 * Copyright：Zix
 * Author：Zix
 * Date：2015/07/05
 * modification history:
 *    1.完成基本布局
 *
 * Version：0.2
 * Copyright：Zix
 * Author：Zix
 * Date：2015/08/05
 * modification history:
 *    1.实现数字键和运算符键的点击响应
 *
 * Version：0.3
 * Copyright：Zix
 * Author：Zix
 * Date：2015/09/24
 * modification history:
 *    1.实现功能键的响应及加减乘除和括号的运算
 *
 * Version：0.4
 * Copyright：Zix
 * Author：Zix
 * Date：2015/09/25
 * modification history:
 *    1.修复回删计算已完成的表达式时未删除等号前运算符建可用的BUG
 *    2.除法错误
 *    3.实现Ans键功能并去除结果中尾部多余的0和小数点
 * TODO:
 *    1.界面修改
 *    2.键盘不响应无效按键
 *
 * Version：1.0
 * Copyright：Zix
 * Author：Zix
 * Date：2016/05/14
 * modification history:
 *    1.更换表达式计算类,支持复杂数学表达式计算和更多运算符
 *    2.除法错误
 *    3.实现Ans键功能并去除结果中尾部多余的0和小数点
 *
 * Version：1.1
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/09
 * modification history:
 *    1.界面重新设计,更美观适用
 *    2.将对运算符的定义移至新头文件metacharacter.h中,提高扩展性和可读性
 *    3.重写对按键的输入响应函数,大幅度减少冗余代码
 *    4.移除按键的可用状态动态改变功能
 *    5.添加对角度符号的支持
 *
 * Version：1.2
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/10
 * modification history:
 *    1.重新实现
 *    2.将对运算符的定义移至新头文件metacharacter.h中,提高扩展性和可读性
 *    3.表达式输入框和结果框分离
 *    4.表达式计算库错误修复及优化
 *    5.添加注释
 *
 * Version：1.2
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/11
 * modification history:
 *    1.编写README.md
 *****************************************************************************/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
