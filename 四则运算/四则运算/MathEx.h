#pragma once
#ifndef MATHEX_H
#define MATHEX_H

#include <string>

using std::string;

namespace MathExError
{
	//除数为0
	const string DIVISOR_ERROR = "Divisor cannot be zero.";
	//根指数为0
	const string RADICAL_EXPONENT_ERROR = "Radical exponent cannot be zero";
	//根指数和被开方数冲突
	const string EXTRACT_ROOT_ERROR = "Radicand and radical exponent are conflicting.";
	//模运算两数不全为整数
	const string MOD_ERROR = "Both dividend and modulus need be a integer.";
	//模数为0
	const string MODULUS_ERROR = "Modulus cannot be zero";
	//0的幂指数为非正数
	const string POW_ERROR = "The exponent connot be a non-zero negative number when the base is zero";
	//非自然数的阶乘
	const string FACTORIAL_ERROR = "Factorial is defined for natural numbers.";
	//正切函数的自变量取值错误
	const string TAN_ERROR = "Tangent error";
	//反正弦，余弦函数自变量取值范围[-1,1]
	const string ARCSIN_ARCCOS_ERROR = "The absolute value of x of arcsin x or arccos x cannot be great than 1";
	//对数的真数为非正数
	const string ANTILOGARITHM_ERROR = "The antilogarithm cannot be  zero or a negative";
	//未知异常
	const string UNKNOWN_ERROR = "unknown error";
}

const double PI = 3.14159265358979323846;

class MathEx
{
private:
	double EPS = 1e-15;
public:
	MathEx();
	~MathEx();

	void set_eps(double e);

	//加法运算
	double op_add(const double &op1, const double &op2) const;
	//减法运算
	double op_subtract(const double &op1, const double &op2) const;
	//乘法运算
	double op_multiply(const double &op1, const double &op2) const;
	//除法运算
	double op_divide(const double &op1, const double &op2) const;
	//模运算
	double op_mod(const double &op1, const double &op2) const;
	//乘方运算
	double op_pow(const double &op1, const double &op2) const;
	//开方运算
	double op_extract_root(const double &op1, const double &op2) const;
	//阶乘运算
	double op_factorial(const double &op) const;
	//正弦运算，op为弧度
	double op_sin(const double &op) const;
	//余弦运算，op为弧度
	double op_cos(const double &op) const;
	//正切运算，op为弧度
	double op_tan(const double &op) const;
	//反正弦运算，返回值为弧度
	double op_arcsin(const double &op) const;
	//反余弦运算，返回值为弧度
	double op_arccos(const double &op) const;
	//反正切运算，返回值为弧度
	double op_arctan(const double &op) const;
	//常用对数，底数为10
	double op_lg(const double &op) const;
	//自然对数，底数为e
	double op_ln(const double &op) const;
};

#endif // !MATHEX_H
