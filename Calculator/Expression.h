#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <list>
#include <string>
#include <stack>
#include <map>
#include "MathEx.h"
#include "metacharacter.h"

using namespace std;

//异常命名空间
namespace ExpressionError
{
	//非法字符
    const string ILLEGAL_CHARACTER_ERROR = "非法字符: ";
	//括号不匹配
    const string ILLEGAL_BRACKET_ERROR = "括号不匹配";
	//缺失操作数
    const string MISSING_OPERAND_ERROR = "缺少操作数";
    //多余的操作数
    const string MISSING_OPERATOR_ERROR = "缺少运算符";
    //百分号前只能为数字或括号包围的表达式
    const string PERCENT_OPERATOR_ERROR = "百分号前只能为数字或括号包围的表达式";
    //角度符号前只能为数字或括号包围的表达式
    const string DEGREE_OPERATOR_ERROR = "角度符号前只能为数字或括号包围的表达式";
    //在优先级大于开平方运算符的运算符之后的开平方运算需要用括号包围
    const string SQUARE_ROOT_ERROR = "开平方运算需要用括号包围";
	//未知异常
    const string UNKNOWN_ERROR = "未知错误";
}

class Expression
{
private:
	//数学计算
	MathEx mathEx;
	//原始字符串
	string raw_exp;
	//拆分后的表达式元素列表
    list<Metacharacter> exp;
	//操作符栈
    stack<Metacharacter> op;
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
    //度符号检测及处理
    void degreeOperatorPreprocessing();
	//不同括号检测及处理
	void bracketPreprocessing();
	//特殊运算符检测及处理
	void preprocessing();
	//出栈运算符运算
	void operation();
	//转换成后缀表达式，边转换边求值
	void transToPostfix();
	//单目运算符运算
    void calc(Metacharacter mc, double &op1);
	//双目运算符运算
    void calc(Metacharacter mc, double &op1, double &op2);
public:
    Expression(string str, int precision = 5);
	~Expression();
	//获取计算结果
	string getResult();
};


#endif
