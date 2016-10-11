##表达式运算计算器
本项目是基于数学表达式计算库开发的一个计算器,界面通过Qt实现。
## 依赖
* qmake >= 5.3

## 编译安装
1. 确保依赖已满足
2. 编译:
````
$ mkdir build
$ cd build
$ qmake ..
$ make
````
3. 安装:
````
$ sudo make install
````

##运行界面
![](https://github.com/Zix777/Complex-mathematical-expressions/blob/master/screenshot/sp20161010_212107.png)![](https://github.com/Zix777/Complex-mathematical-expressions/blob/master/screenshot/sp20161010_214051.png)

##使用说明
- `↑`键用于切换`sin` `cos` `tan` `lg`为`arcsin` `arccos` `arctan` `ln`
- `←`键用于删除前一个输入的数字或运算符
- `C`键清空输入框
- `Ans`用于输入上次计算结果