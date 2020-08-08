## GDB

GDB 是一个由 GNU 开源组织发布的、UNIX/LINUX 操作系统下的、基于命令行的程序调试工具。

有一个 cpp 文件名为 `1.cpp`，`g++ -g 1.cpp -o 1` 生成可执行程序名为 1。

```cpp
// 1.cpp
#include<bits/stdc++.h>
using namespace std;

void fun() {
	int b = 100;
	printf("b = %d\n", b);
}

int main() {
	int a = 10;
	int arr[10] = {0,1,2,3,4,5,6};
	printf("a = %d\n", a);
	fun();
	int i = 1;
	while(i <= 3) {
		printf("i*i = %d\n",i*i);
		++i;
	}
	return 0;
}
```



## 基础

GDB 启动

+ `gdb 1`
+ `gdb`，进入 GDB 后调用 `file 1` 加载程序



GDB 中的指令：

+ 回车键，运行上一个指令
+ `run` 或 `r`：运行程序
+ `quit` 或 `q`：退出 GDB
+ `break` 或 `b`：设置断点，设置断点后会运行到断点的前一行
  + `b 函数名`：如 `b main`，在函数开头设置断点。
  + `b 文件名:行号`：如 `b 1.cpp:12` 此文件第 12 行设置断点。
+ `continue` 或 `c`：继续运行
+ `next` 或 `n`：单步执行
+ `step` 或 `s`：陷入到函数
+ `list 数字` 或 `l 数字`：显示指定行号附近代码
+ `p 变量`：显示变量值，还支持打印数组（可以带索引）
+ `info` 或 `i`，后面跟需要查询的信息
  + `i b`：查询设置了哪些断点
  + `i r`：查询寄存器信息
+ `delete` 或 `d`：默认删除全部断点，加序号（非行号）删除指定断点。



一些其他操作

`b 15 if i == 2`：第 15 行，i 变量值等于 2 处设置断点。

`finish`：运行到函数返回，并打印函数返回时的堆栈地址和返回值及参数值等信息。

`until 行号` 或 `u 行号`：运行到目标行号

`call 函数`：当前位置执行某函数，如 `call fun()`

`signal 信号`：产生某信号

`shell 命令`：使用 shell 执行命令



## 多线程调试

待

