#include "Expression.h"
#include <exception>
#include <regex>
#include <cctype>
#include <cmath>
#include <iostream>
using namespace std;



Expression::Expression(string str, int precision)
{
	raw_exp = str;
    mathEx.set_eps(precision);
}

Expression::~Expression()
{
}

/*
 * 对表达式进行初步合法性检查，包括字符以及字符组成的运算单元是否合法
 */
bool Expression::simpleCheck()
{
	string temp;
    bool getWord = false;   //获取操作符中
    int isAlpha = 0;    //当前字符是否为字母
	for (auto &i : raw_exp)
	{
        isAlpha = isalpha(i);   //判断当前字符是否为字母
        if (getWord)
		{
            /*
             * 处于操作词构成过程中，继续添加字母
             */
			if (isAlpha)
			{
				temp += i;
                continue;   //跳过后续
			}
		}
		else
		{
            /*
             * 读取到一个字母，开启操作词构成过程
             */
			if (isAlpha)
			{
				getWord = true;
				temp += i;
                continue;   //跳过后续
			}
			else
                temp += i;  //读取到非字母，操作词构成过程结束
		}

        /*
         * 如果读取到的操作词不在元字符表中或为结束符，抛出异常
         */
        if (METACHARACTERS.find(temp) == METACHARACTERS.end() || temp == "$")
            throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + temp);

        /*
         * 重置操作词构成过程标识
         */
		if (getWord)
		{
			getWord = false;
		}
        temp = "";  //清空
	}

	if (getWord)
		throw runtime_error(ExpressionError::ILLEGAL_BRACKET_ERROR);
	return true;
}

/*
 * 词法分析，构字成词
 */
bool Expression::split()
{
	string::size_type i = 0;
	string::size_type temp = 0;
	while (i<raw_exp.size())
	{
		string str_temp;
		str_temp += raw_exp[i];
        bool getPoint = false;
        if (isdigit(raw_exp[i]))    //读取数字
		{
			temp = i;
			do
			{
                if(raw_exp[i] == '.')
                    getPoint = true;
				if (++i >= raw_exp.size())
					break;
            } while (isdigit(raw_exp[i]) || ((!getPoint) && raw_exp[i] == '.'));
            exp.push_back(Metacharacter{ 0,0,0,0,0, raw_exp.substr(temp, i - temp) });
		}
        else if (raw_exp[i] == '.') //读取到不在数字之后的小数点，抛出异常
			throw runtime_error(ExpressionError::ILLEGAL_CHARACTER_ERROR + ".");
        else if (METACHARACTERS.find(str_temp)!=METACHARACTERS.end()) //读取到操作符
		{
            exp.push_back(METACHARACTERS.at(str_temp));
			++i;
		}
        else if (isalpha(raw_exp[i]))   //读取到操作词
		{
			temp = i;
			do
			{
				if (++i >= raw_exp.size())
					break;
			} while (isalpha(raw_exp[i]));
			str_temp = raw_exp.substr(temp, i - temp);
            exp.push_back(METACHARACTERS.at(str_temp));
		}
	}
	return true;
}

/*
 * 负号处理
 */
void Expression::negativeOperatorPreprocessing()
{
    for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "-")
		{
            //如果负号在表达式首位，在负号前添加数字0
			if (i == exp.begin())
			{
                i = exp.insert(i, METACHARACTERS.at("0"));
			}
			else
			{
                //如果负号前为括号，在负号前添加数字0
				--i;
				if ((*i).out_priority >= 100)
				{
					++i;
                    i = exp.insert(i, METACHARACTERS.at("0"));
				}
				++i;
			}
		}
	}
}

//查找开平方运算并替换为开平方运算符
void Expression::sqrtOperatorPreprocessing()
{
    for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "#")
		{
			//如果根号在表达式第一个位置
			if (i == exp.begin())
			{
                *i = METACHARACTERS.at("<");
			}
			else
			{
				--i;
                //如果根号前为左括号,前置运算符或中置运算符,为开平方
                if ((*i).out_priority >= 100 || (*i).position == 1 || (*i).position == 2)
                {
                    if(i->type == 1 && i->in_priority >= METACHARACTERS.at("<").in_priority)
                        throw runtime_error(ExpressionError::SQUARE_ROOT_ERROR);
                    ++i;
                    *i = METACHARACTERS.at("<");
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
    for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		if ((*i).e == "%")
		{
			++i;
            /*
             * 如果%后为表达式尾,中置或后置运算符,则%为百分号运算,为避免二义性,将其替换为百分号运算
             */
			if (i == exp.end() || (*i).position == 2 || (*i).position == 3)
			{
                /*
                 * 百分号前只能为数字或括号包围的表达式
                 */
                --i;--i;
                if(i->type!=0 && i->in_priority<=100)
                    throw runtime_error(ExpressionError::PERCENT_OPERATOR_ERROR);
                ++i;
                *i = METACHARACTERS.at(">");
			}
		}
    }
}

/**
 * 为了保证°的优先计算,对其及前面的数字加上括号
 */
void Expression::degreeOperatorPreprocessing()
{
    //与对百分号处理类似,只是无需对后一个操作词进行判断,°无二义性
    for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
    {
        if ((*i).e == "`")
        {
            /*
             * 角度前只能为数字或括号包围的表达式
             */
            --i;
            if(i->type!=0 && i->in_priority<=100)
                throw runtime_error(ExpressionError::DEGREE_OPERATOR_ERROR);
            ++i;
        }
    }
}

//将大/中操作转换为对应的小括号
void Expression::bracketPreprocessing()
{
    for (list<Metacharacter>::iterator i = exp.begin(); i != exp.end(); ++i)
	{
		//转换左括号
		if ((*i).out_priority ==101 || (*i).out_priority == 102)
		{
			i = exp.erase(i);
            i = exp.insert(i, METACHARACTERS.at("("));
		}
		//转换右括号
		else if ((*i).in_priority == 101 || (*i).in_priority == 102)
		{
			i = exp.erase(i);
            i = exp.insert(i, METACHARACTERS.at(")"));
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
    degreeOperatorPreprocessing();
}

void Expression::operation()
{
    if (op.top().operand == 1)  //若为一元运算符
	{
		double op1; if (op.empty())
			throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
		else
			calc(op.top(), op1);
	}
    else    //若为二元运算符
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
        exp.push_front(METACHARACTERS.at("$"));
		for (auto i : exp)
		{
			//如果当前元素为操作数，压入操作数栈
			if (i.type == 0)
				number.push(stod(i.e));
			//如果当前元素为运算符，比较其与运算符栈顶元素的优先级
			else if (i.type == 1)
			{
                /*
                 * 如果小于栈顶运算符优先级，
                 * 不断出栈栈顶运算符直到栈顶运算符优先级小于当前运算符优先级，
                 * 并依次对出栈的运算符进行运算
                 * 然后入栈当前运算符
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
				//如果当前括号为左括号，入栈
				if (i.out_priority > 0)
				{
					op.push(i);
					//lastBracket = i;
				}
				//如果当前括号为右括号，出栈运算符栈直到遇到第一个左括号
				else if (i.out_priority < 0)
				{
//					//一对括号内无内容，抛出括号异常
//					if (op.top().out_priority>100)
//						throw runtime_error(ExpressionError::NEEDLESS_BARCKET_ERROR);

                    while (op.top().type != 2)
					{
						operation();
                    }

					op.pop();
					if (op.empty())
						throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
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

        if(number.size() > 1)
        {
            throw runtime_error(ExpressionError::MISSING_OPERATOR_ERROR);
        }
	}
	catch (...) {
		throw;
	}
}

//单目运算符运算
void Expression::calc(Metacharacter mc, double & op1)
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
        else if (mc.e == "`")
            number.push(mathEx.op_degree_to_radian(op1));
        else if (mc.e == ">")
            number.push(mathEx.op_percent(op1));
        else if (mc.e == "<")
            number.push(mathEx.op_square_root(op1));
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
void Expression::calc(Metacharacter mc, double & op1, double & op2)
{
    if (number.empty()) //数字栈为空,缺少操作数2
		throw runtime_error(ExpressionError::MISSING_OPERAND_ERROR);
	else
	{
		op2 = number.top();
		number.pop();
	}
    if (number.empty()) //数字栈为空,缺少操作数1
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

/*
 * 计算
 */
string Expression::getResult()
{
	try {
        simpleCheck();  //字符合法性检查
        split();    //构字成词
        preprocessing();    //特殊运算符预处理
        transToPostfix();   //转换为逆波兰式并计算
//        for (auto &i : exp)
//        {
//            cout << i.e << ' ';
//        }
    } catch (runtime_error &){
		throw;
	}
    result = number.top();  //数字栈中最后一个数即为结果
    return to_string(mathEx.getRound(result));
}


