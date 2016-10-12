/******************************************************************************
 * metacharacter.h - 运算符定义类
 *
 * Copyright (c) 20015-2016  Zix
 *
 * DESCRIPTION: -
 *   包含对运算符属性的相关定义
 *
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/09
 * modification history:
 *    1.新增对运算符在图形界面显示的字符的常量定义,便于后期使用
 *    2.修改部分运算符的优先级
 *    3.添加角度符号相关定义
 *
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/10
 * modification history:
 *    1.添加独立的百分号和开平方符号定义
 *    2.修改部分符号的优先级
 *
 ******************************************************************************/
#ifndef METACHARACTER
#define METACHARACTER
#include <string>
#include <map>

struct Metacharacter {
    //0为数字（包括小数点），1为运算符，2为括号
    int type;
    //栈外优先级，数字为0
    int out_priority;
    //栈内优先级，数字为0
    int in_priority;
    //操作数个数，数字和括号为0
    int operand;
    /*运算符位置，数字和括号为0
     *运算符在操作数之前，之间和之后分别为1,2和3表示
     */
    int position;
    //运算符元素
    string e;
};

/*
 * 各符号的属性表
 */
const map<string, Metacharacter> METACHARACTERS{
    /*
     * 数字0-9和小数点
     */
    { "0",		Metacharacter{ 0,0,0,0,0, "0" }},
    { "1",		Metacharacter{ 0,0,0,0,0, "1" }},
    { "2",		Metacharacter{ 0,0,0,0,0, "2" }},
    { "3",		Metacharacter{ 0,0,0,0,0, "3" }},
    { "4",		Metacharacter{ 0,0,0,0,0, "4" }},
    { "5",		Metacharacter{ 0,0,0,0,0, "5" }},
    { "6",		Metacharacter{ 0,0,0,0,0, "6" }},
    { "7",		Metacharacter{ 0,0,0,0,0, "7" }},
    { "8",		Metacharacter{ 0,0,0,0,0, "8" }},
    { "9",		Metacharacter{ 0,0,0,0,0, "9" }},
    { ".",		Metacharacter{ 0,0,0,0,0, "." }},

    /*
     * 加减乘除
     */
    { "+",		Metacharacter{ 1,1,1,2,2, "+" }},
    { "-",		Metacharacter{ 1,1,1,2,2, "-" }},
    { "*",		Metacharacter{ 1,2,2,2,2, "*" }},
    { "/",		Metacharacter{ 1,2,2,2,2, "/" }},

    { "%",		Metacharacter{ 1,2,2,2,2, "%" }},   //求余或百分号
    { "^",		Metacharacter{ 1,3,3,2,2, "^" }},   //乘方
    { "#",		Metacharacter{ 1,3,3,2,2, "#" }},   //开多次方
    { "<",		Metacharacter{ 1,4,4,1,1, "<" }},   //开平方
    { "!",		Metacharacter{ 1,4,4,1,3, "!" }},   //阶层

    { "sin",	Metacharacter{ 1,11,11,1,1, "sin" }},   //正弦（默认弧度）
    { "cos",	Metacharacter{ 1,11,11,1,1, "cos" }},   //余弦
    { "tan",	Metacharacter{ 1,11,11,1,1, "tan" }},   //正切
    { "arcsin",	Metacharacter{ 1,11,11,1,1, "arcsin" }},    //反正弦
    { "arccos",	Metacharacter{ 1,11,11,1,1, "arccos" }},    //反余弦
    { "arctan",	Metacharacter{ 1,11,11,1,1, "arctan" }},    //反正切
    { "lg",		Metacharacter{ 1,11,11,1,1, "lg" }},    //常用对数，以10为底
    { "log",	Metacharacter{ 1,11,11,1,1, "log" }},   //常用对数，以10为底
    { "ln",		Metacharacter{ 1,11,11,1,1, "ln" }},    //自然对数，以e为底

    { "`",		Metacharacter{ 1,20,20,1,3, "`" }},   //度(角度)
    { ">",		Metacharacter{ 1,20,20,1,3, ">" }},   //百分号

    /*
     * 括号，程序未区分括号形式和优先级，即5*(3+1}是合法的
     */
    { "(",		Metacharacter{ 2,103,-1,0,0, "(" }},
    { "[",		Metacharacter{ 2,102,-1,0,0, "[" }},
    { "{",		Metacharacter{ 2,101,-1,0,0, "{" }},
    { ")",		Metacharacter{ 2,-1,103,0,0, ")" }},
    { "]",		Metacharacter{ 2,-1,102,0,0, "]" }},
    { "}",		Metacharacter{ 2,-1,101,0,0, "}" }},

    { "$",		Metacharacter{ 3,-10,-10,0,0, "$" }},   //结束符号
};

/*
 * 用于在图形化界面显示的字符
 */
const string ZERO = "0";
const string ONE = "1";
const string TWO = "2";
const string THREE = "3";
const string FOUR = "4";
const string FIVE = "5";
const string SIX = "6";
const string SEVEN = "7";
const string EIGHT = "8";
const string NINE = "9";
const string POINT = ".";
const string ADD = "+";
const string MINUS = "-";
const string MULTIPLY = "×";
const string DIVIDE = "÷";
const string EQUAL = "=";
const string DEGREE = "°";
const string MOD_PERCENT = "%";
const string POW = "^";
const string EXTRACT_ROOT = "√";
const string FACTORIAL = "!";
const string SIN = "sin";
const string COS = "cos";
const string TAN = "tan";
const string ARCSIN = "arcsin";
const string ARCCOS = "arccos";
const string ARCTAN = "arctan";
const string LG = "lg";
const string LOG = "log";
const string LN = "ln";
const string LEFT_BRACKET = "(";
const string RIGHT_BRACKET = ")";

#endif // METACHARACTER

