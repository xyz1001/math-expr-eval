#include <iostream>
#include "Expression.h"	//导入Expression头文件

using namespace std;

int main()
{
	while (1)
	{
		string str;
		cin >> str;
		Expression e(str, 5);	//传入输入的表达式,小数点保留5位
		try
		{
			cout << e.getResult() << endl;	//读取计算结果
		}
		catch (runtime_error err)	//捕获异常
		{
			cerr << err.what() << endl;
		}
	}
	cin.get();
	cin.get();
	return 0;
}