/******************************************************************************
 * MathEx.h - 数学计算类
 *
 * Copyright (c) 20015-2016  Zix
 *
 * DESCRIPTION: -
 *   对cmath类的进一步封装及添加,实现对错误的捕获
 *
 * Copyright：Zix
 * Author：Zix
 * Date：2016/5/13
 * modification history:
 *    1.支持常见运算符的运算
 *
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/09
 * modification history:
 *    1.新增对角度符号的运算,将其转换为弧度
 *    2.新增对结果进行保留设定小数位的函数getRound();
 *
 * Copyright：Zix
 * Author：Zix
 * Date：2016/10/10
 * modification history:
 *    1.新增百分号运算和开平方运算
 *
 ******************************************************************************/
#ifndef MATHEX_H
#define MATHEX_H

#include <string>

using namespace std;

namespace MathExError
{
	//除数为0
    const string DIVISOR_ERROR = "除数不能为0";
    //被开方数不能小于0
    const string RADICAND_ERROR = "被开方数不能小于0";
    //负数不存在平方根
    const string EXTRACT_ROOT_ERROR = "负数不存在平方根";
	//模运算两数不全为整数
    const string MOD_ERROR = "模运算两操作数需均为整数";
	//模数为0
    const string MODULUS_ERROR = "模数不能为0";
	//0的幂指数为非正数
    const string POW_ERROR = "0的幂指数不能为非正数";
	//非自然数的阶乘
    const string FACTORIAL_ERROR = "阶乘数需为自然数";
	//正切函数的自变量取值错误
    const string TAN_ERROR = "正切函数自变量取值不能为kπ+π/2";
	//反正弦，余弦函数自变量取值范围[-1,1]
    const string ARCSIN_ARCCOS_ERROR = "反正弦和反余弦函数自变量绝对值不能大于1";
	//对数的真数为非正数
    const string ANTILOGARITHM_ERROR = "对数的真数不能为非正数";
	//未知异常
    const string UNKNOWN_ERROR = "未知异常";
}

const double PI = 3.14159265358979323846;

class MathEx
{
private:
    double EPS = 1e-4;  //小数精度
public:
	MathEx();
	~MathEx();

    void set_eps(int e);    //设置精度,e为小数点位数
    double getRound(double d) const;    //根据精度四舍五入

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
    //开平方运算
    double op_square_root(const double &op) const;
	//开方运算
	double op_extract_root(const double &op1, const double &op2) const;
	//阶乘运算
	double op_factorial(const double &op) const;
    //阶乘运算
    double op_percent(const double &op) const;
    //角度转弧度
    double op_degree_to_radian(const double &op) const;
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
