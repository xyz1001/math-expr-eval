#include "Expression.h"
#include <exception>
#include <stdexcept>
#include <regex>
#include <cctype>
#include <cmath>
#include <iostream>
using namespace std;

const map<string, metacharacter> Expression::METACHARACTER{
	{ "0",		metacharacter{ 0,0,0,0,0, "0" }},
	{ "1",		metacharacter{ 0,0,0,0,0, "1" }},
	{ "2",		metacharacter{ 0,0,0,0,0, "2" }},
	{ "3",		metacharacter{ 0,0,0,0,0, "3" }},
	{ "4",		metacharacter{ 0,0,0,0,0, "4" }},
	{ "5",		metacharacter{ 0,0,0,0,0, "5" }},
	{ "6",		metacharacter{ 0,0,0,0,0, "6" }},
	{ "7",		metacharacter{ 0,0,0,0,0, "7" }},
	{ "8",		metacharacter{ 0,0,0,0,0, "8" }},
	{ "9",		metacharacter{ 0,0,0,0,0, "9" }},
	{ ".",		metacharacter{ 0,0,0,0,0, "." }},

	{ "+",		metacharacter{ 1,1,1,2,2, "+" }},
	{ "-",		metacharacter{ 1,1,1,2,2, "-" }},
	{ "*",		metacharacter{ 1,2,2,2,2, "*" }},
	{ "/",		metacharacter{ 1,2,2,2,2, "/" }},
	{ "%",		metacharacter{ 1,2,2,2,2, "%" }},
	{ "^",		metacharacter{ 1,3,3,2,2, "^" }},
	{ "#",		metacharacter{ 1,3,3,2,2, "#" }},
	{ "!",		metacharacter{ 1,4,4,1,3, "!" }},

	{ "sin",	metacharacter{ 1,11,11,1,1, "sin" }},
	{ "cos",	metacharacter{ 1,11,11,1,1, "cos" }},
	{ "tan",	metacharacter{ 1,11,11,1,1, "tan" }},
	{ "arcsin",	metacharacter{ 1,11,11,1,1, "arcsin" }},
	{ "arccos",	metacharacter{ 1,11,11,1,1, "arccos" }},
	{ "arctan",	metacharacter{ 1,11,11,1,1, "arctan" }},
	{ "lg",		metacharacter{ 1,11,11,1,1, "lg" }},
	{ "log",	metacharacter{ 1,11,11,1,1, "log" }},
	{ "ln",		metacharacter{ 1,11,11,1,1, "ln" }},

	{ "(",		metacharacter{ 2,103,-1,0,0, "(" }},
	{ "[",		metacharacter{ 2,102,-1,0,0, "[" }},
	{ "{",		metacharacter{ 2,101,-1,0,0, "{" }},
	{ ")",		metacharacter{ 2,-1,103,0,0, ")" }},
	{ "]",		metacharacter{ 2,-1,102,0,0, "]" }},
	{ "}",		metacharacter{ 2,-1,101,0,0, "}" }},

	{ "$",		metacharacter{ 3,-10,-10,0,0, "$" }},
};

Expression::Expression(string str)
{
	raw_exp = str;
}

Expression::~Expression()
{
}

bool Expression::simpleCheck()
{
	string temp;
	bool getWord = false;
	int isAlpha = 0;
	for (auto &i : raw_exp)
	{
		isAlpha = isalpha(i);
		if (getWord)
		{
			if (isAlpha)
			{
				temp += i;
				continue;
			}
		}
		else
		{
			if (isAlpha)
			{
				getWord = true;
				temp += i;
				continue;
			}
			else
				temp += i;
		}
		if (getWord)
		{
			if (METACHARACTER.find(temp) == METACHARACTER.end() || temp == "$")
				throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + temp);
			getWord = false;
		}

		if (METACHARACTER.find(temp) == METACHARACTER.end() || temp == "$")
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + temp);
		temp = "";
	}

	if (getWord)
		throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
	return true;
}

bool Expression::split()
{
	string::size_type i = 0;
	string::size_type temp = 0;
	while (i<raw_exp.size())
	{
		string str_temp;
		str_temp += raw_exp[i];
		if (isdigit(raw_exp[i]))
		{
			temp = i;
			do
			{
				if (++i >= raw_exp.size())
					break;
			} while (isdigit(raw_exp[i]) || raw_exp[i] == '.');
			exp.push_back(metacharacter{ 0,0,0,0,0, raw_exp.substr(temp, i - temp) });
		}
		else if (raw_exp[i] == '.')
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + ".");
		else if (METACHARACTER.find(str_temp)!=METACHARACTER.end())
		{
			exp.push_back(METACHARACTER.at(str_temp));
			++i;
		}
		else if (isalpha(raw_exp[i]))
		{
			temp = i;
			do
			{
				if (++i >= raw_exp.size())
					break;
			} while (isalpha(raw_exp[i]));
			str_temp = raw_exp.substr(temp, i - temp);
			exp.push_back(METACHARACTER.at(str_temp));
		}
	}
	return true;
}

void Expression::negativeOperatorPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "-")
		{
			if (i == exp.begin())
			{
				i = exp.insert(i, METACHARACTER.at("0"));
			}
			else
			{
				--i;
				if ((*i).out_priority >= 100)
				{
					++i;
					i = exp.insert(i, METACHARACTER.at("0"));
				}
				++i;
			}
		}
	}
}

//为默认省略根指数2的开平方运算符前添加上根指数2
void Expression::sqrtOperatorPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "#")
		{
			//如果根号在表达式第一个位置
			if (i == exp.begin())
			{
				i = exp.insert(i, METACHARACTER.at("2"));
			}
			else
			{
				--i;
				//如果根号前为左括号，直接添加根指数2
				if ((*i).out_priority >= 100)
				{
					++i;
					i = exp.insert(i, METACHARACTER.at("2"));
					++i;
				}
				//如果根号前为为前置运算符或中置运算符，说明根号为开平方运算，为其添加根指数2并添加括号
				else if ((*i).position == 1 || (*i).position == 2)
				{
					//在根号前添加“（2”
					++i;
					i = exp.insert(i, { METACHARACTER.at("("),METACHARACTER.at("2") }); //(2#4
					++i, ++i, ++i;
					//如果根号后为数字，直接在数字后添加“)”
					if ((*i).type == 0)
					{
						++i;
						i = exp.insert(i, METACHARACTER.at(")"));
					}
					//如果根号后为左括号，查找对应的右括号并在其后添加“)”
					else if ((*i).type == 2)
					{
						int bracketCnt = 1;
						for (auto j = ++i; j != exp.end(); ++j)
						{
							if ((*j).out_priority > 100)
								++bracketCnt;
							else if ((*j).in_priority > 100)
								--bracketCnt;

							if (bracketCnt == 0)
							{
								++j;
								exp.insert(j, METACHARACTER.at(")"));
								break;
							}
						}
						--i;
						//如果根号后左右括号数量不等，抛出括号异常
						if (bracketCnt != 0)
							throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
					}
					//如果根号后为运算符或右括号，抛出操作数异常
					else if ((*i).type == 1 || (*i).out_priority > 100)
						throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
					//其他异常
					else
						throw runtime_error(ExpressionError::UNKNOWN_ERROR);
				}
				else
					++i;
			}
		}
	}
}

//根据下文对%进行判断，如果下文为表达式尾或中置和后置运算符，则%为百分号操作，否则为模操作
void Expression::percentOperatorPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "%")
		{
			++i;
			if (i == exp.end() || (*i).position == 2 || (*i).position == 3)
			{
				i = exp.insert(i, metacharacter{ 0,0,0,0,0, "100" });
				--i;
				(*i).e = "/";
			}
		}
	}
}

//将大/中操作转换为对应的小括号
void Expression::bracketPreprocessing()
{
	for (list<metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		//转换左括号
		if ((*i).out_priority ==101 || (*i).out_priority == 102)
		{
			i = exp.erase(i);
			i = exp.insert(i, METACHARACTER.at("("));
		}
		//转换右括号
		else if ((*i).in_priority == 101 || (*i).in_priority == 102)
		{
			i = exp.erase(i);
			i = exp.insert(i, METACHARACTER.at(")"));
		}
	}
}

//对分割后的表达式进行预处理，便于接下来的操作
void Expression::preprocessing()
{
	negativeOperatorPreprocessing();
	sqrtOperatorPreprocessing();
	percentOperatorPreprocessing();
	bracketPreprocessing();
}

void Expression::operation()
{
	if (op.top().operand == 1)
	{
		double op1; if (op.empty())
			throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
		else
			calc(op.top(), op1);
	}
	else
	{
		double op1, op2;
		if (op.empty())
			throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
		else
			calc(op.top(), op1, op2);
	}
	op.pop();
}


void Expression::transToPostfix()
{
	try {
		//metacharacter lastBracket;
		exp.push_front(METACHARACTER.at("$"));
		//exp.push_back(elementOfExpression{ "$",-2 });
		for (auto i : exp)
		{
			//如果当前元素为操作数，压入操作数栈
			if (i.type == 0)
				number.push(stod(i.e));
			//如果当前元素为运算符，比较其与运算符栈顶元素的优先级
			else if (i.type == 1)
			{
				/*如果小于栈顶运算符优先级，
				 *不断出栈栈顶运算符直到栈顶运算符优先级小于当前运算符优先级，
				 *并依次对出栈的运算符进行运算
				 *然后入栈当前运算符
				 */
				if (i.out_priority <= op.top().in_priority)
				{
					do
					{
						operation();
					} while (i.out_priority <= op.top().in_priority);
				}
				op.push(i);
			}
			//如果当前运算符为括号
			else if (i.type == 2)
			{
				/*如果是表达式的第一个括号，将其保存至lastBracket
				if (lastBracket.e == "")
				{
					op.push(i);
					lastBracket = i;
					continue;
				}*/

				//如果当前括号为左括号，入栈
				if (i.out_priority > 0)
				{
					op.push(i);
					//lastBracket = i;
				}
				//如果当前括号为右括号，出栈运算符栈直到遇到第一个左括号
				else if (i.out_priority < 0)
				{
					//一对括号内无内容，抛出括号异常
					if (op.top().out_priority>100)
						throw runtime_error(ExpressionError::NEEDLESS_BARCKET_ERROR);

					do
					{
						operation();
					}while (op.top().type != 2);

					op.pop();
					if (op.empty())
						throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
					//不同类型的括号匹配检测
					/*else
					{
						if (op.top().in_priority != i.out_priority)
						{
							throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
						}
						else
						{
							op.pop();
						}
					}*/
				}
			}
			//表达式边缘标识符$直接压入运算符栈
			else if (i.type == 3)
				op.push(i);
		}

		//对运算符栈剩余的运算符依次出栈并进行运算
		while (op.size() > 1)
		{
			operation();
		}
	}
	catch (...) {
		throw;
	}
}

//单目运算符运算
void Expression::calc(metacharacter mc, double & op1)
{
	if (number.empty())
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op1 = number.top();
		number.pop();
	}
	try {
		if (mc.e == "!")
			number.push(mathEx.op_factorial(op1));
		else if (mc.e == "sin")
			number.push(mathEx.op_sin(op1));
		else if (mc.e == "cos")
			number.push(mathEx.op_cos(op1));
		else if (mc.e == "tan")
			number.push(mathEx.op_tan(op1));
		else if (mc.e == "arcsin")
			number.push(mathEx.op_arcsin(op1));
		else if (mc.e == "arccos")
			number.push(mathEx.op_arccos(op1));
		else if (mc.e == "arctan")
			number.push(mathEx.op_arctan(op1));
		else if (mc.e == "log" || mc.e == "lg")
			number.push(mathEx.op_lg(op1));
		else if (mc.e == "ln")
			number.push(mathEx.op_ln(op1));
		else
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + mc.e);
	}
	catch (runtime_error) {
		throw;
	}

}

//双目运算符运算
void Expression::calc(metacharacter mc, double & op1, double & op2)
{
	if (number.empty())
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op2 = number.top();
		number.pop();
	}
	if (number.empty())
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op1 = number.top();
		number.pop();
	}
	try {
		if (mc.e == "+")
			number.push(mathEx.op_add(op1, op2));
		else if (mc.e == "-")
			number.push(mathEx.op_subtract(op1, op2));
		else if (mc.e == "*")
			number.push(mathEx.op_multiply(op1, op2));
		else if (mc.e == "/")
			number.push(mathEx.op_divide(op1, op2));
		else if (mc.e == "^")
			number.push(mathEx.op_pow(op1, op2));
		else if (mc.e == "%")
			number.push(mathEx.op_mod(op1, op2));
		else if (mc.e == "#")
			number.push(mathEx.op_extract_root(op1, op2));
		else
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + mc.e);
	}
	catch (runtime_error) {
		throw;
	}
}

string Expression::getResult()
{
	try {
		simpleCheck();
		split();
		preprocessing();
		transToPostfix();
		/*for (auto &i : exp)
		{
			cout << i.e << ' ';
		}*/
	} catch (runtime_error &){
		/*for (auto &i : exp)
		{
			cout << i.e << ' ';
		}*/
		throw;
	}
	result = number.top();
	return to_string(result);
}


