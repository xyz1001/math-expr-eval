#include <iostream>
#include "Expression.h"

using namespace std;

int main()
{
	while (1)
	{
		string str;
		cin >> str;
		Expression e(str);
		try
		{
			cout << e.getResult() << endl;
		}
		catch (runtime_error err)
		{
			cerr << err.what() << endl;
		}
	}
	cin.get();
	cin.get();
	return 0;
}