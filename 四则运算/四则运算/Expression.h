#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <list>
#include <string>
#include <stack>
#include <map>
#include "MathEx.h"

using namespace std;

struct metacharacter {
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

//异常命名空间
namespace ExpressionError
{
	//非法字符
	const string ILLEGAL_CHARACTER_ERROR = "Illegal character: ";
	//括号不匹配
	const string ILLEGAL_BRACKET_ERROR = "Unmatched bracket";
	//多余括号
	const string NEEDLESS_BARCKET_ERROR = "Needless bracket";
	//缺失操作数
	const string MISSING_OPERAND_ERROR = "Missing operand";
	//未知异常
	const string UNKNOWN_ERROR = "Unknown error";
}

class Expression
{
private:
	//表达式元素信息
	const static map<string,metacharacter> METACHARACTER;
	//数学计算
	MathEx mathEx;
	//原始字符串
	string raw_exp;
	//拆分后的表达式元素列表
	list<metacharacter> exp;
	//操作符栈
	stack<metacharacter> op;
	//数字栈
	stack<double> number;
	//表达式的值
	double result = 0;

	//对表达式进行字符合法性的初步检测
	bool simpleCheck();
	//拆分表达式
	bool split();
	//负号检测及处理
	void negativeOperatorPreprocessing();
	//开方负号检测及处理
	void sqrtOperatorPreprocessing();
	//百分号/求余符号检测及处理
	void percentOperatorPreprocessing();
	//不同括号检测及处理
	void bracketPreprocessing();
	//特殊运算符检测及处理
	void preprocessing();
	//出栈运算符运算
	void operation();
	//转换成后缀表达式，边转换边求值
	void transToPostfix();
	//单目运算符运算
	void calc(metacharacter mc, double &op1);
	//双目运算符运算
	void calc(metacharacter mc, double &op1, double &op2);
public:
	Expression(string str);
	~Expression();
	//获取计算结果
	string getResult();
};


#endif