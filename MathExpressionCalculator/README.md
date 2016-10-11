#数学表达式算法库
##下载和使用
1. `git clone git@github.com:Zix777/Complex-mathematical-expressions.git`
2. 复制expression文件夹下除`main.cpp`文件外其他文件至你的代码目录并将其添加至工程中
3. 定义Expression对象并通过`string getResult()`函数获取计算结果,参考`main.cpp`内容

##运行示例
- linux
 1. `git clone git@github.com:Zix777/Complex-mathematical-expressions.git`
 2. `cd Complex-mathematical-expressions/MathExpressionCalculator/`
 3. `make`
 4. `chmod u+x main`
 5. `./main`

- windows
 1. `git clone git@github.com:Zix777/Complex-mathematical-expressions.git`
 2. 通过IDE编译运行即可

输入合法的数学表达式即可输出表达式的计算结果

![示例界面](https://github.com/Zix777/Complex-mathematical-expressions/blob/master/screenshot/sp20161010_214714.png)

##说明
- 实现算法为将表达式转换为逆波兰式(后缀表达式)计算

- `Expression`类为表达式解析类, `MathEx`类定义了各运算符的运算规则, `metacharacter`头文件中定义了常见运算符的属性

- 数学表达式中所使用的符号必须与`metacharacter`头文件中`METACHARACTERS`表规定的一致,调用表达式计算类时一定要先将运算符转换为代码中对应的字符,具体对应如下

标准运算符|代码符号|含义
---------------|-----------|------
`+`|`+`|加法
`-`|`-`|减法
`×`|`*`|乘法
`÷`|`/`|除法
`MOD`|`%`|求余
`%`|`%`或`>`|百分数
上标|`^`|幂
`√￣`|`#`|开方
`√￣`|`<`|开平方
`!`|`!`|阶乘
`sin`|`sin`|正弦
`cos`|`cos`|余弦
`tan`|`tan`|正切
`arcsin`|`arcsin`|反正弦
`arccos`|`arccos`|反余弦
`arctan`|`arctan`|反正切
`lg`|`lg`或`log`|常用对数
`ln`|`ln`|自然对数
`°`|`` ` ``|角度符号

- 代码中使用`double`存储数字,精度有限,不宜进行高精度和大数计算

- 返回值为带小数部分的`string`类型,应视情况去除尾部多余的`0`和小数点

- `Expression`类默认保留5位小数,可通过构造函数第二个参数进行设置

##注意
1. 不支持负数的开方,即使是根指数为奇数的分数.
2. 定义了常见的表达式错误及运算错误,注意捕获异常

##TODO
1. 对高精度运算的支持
2. 对大数运算的支持
3. 小数点位数的动态确定
4. 对`×÷`等符号的预转换
3. 返回值尾部多余`0`的去除
