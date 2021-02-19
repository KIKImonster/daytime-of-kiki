
#include<stdio.h>
#include<iostream>
#include<time.h>


#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
namespace bite
{
	void Printf(int a)
	{
		printf("%d ", a);
	}
	int a;
	int b;
	namespace bite_69//嵌套定义，
	{
		int a;
		int b;
		void fun1(int a)
		{
			printf("%d ", a);
		}
	}
}
//命名空间成员的使用方式
//1.命名空间：+ ：：+ 成员 --》推荐使用这种方式；
//2.引入成员 using + 命名空间 + ：： + 成员，后面使用成员时，不需要加作用域，注意：会暴露在全局域当中，如果有冲突会重定义
//3. 展开命名空间 using + 命名空间： 命名空间所有成员暴露在全局域中；
namespace bite//可以分段定义，编译器会合并相同的命名空间，
	//相同命名空间不能定义相同的
{ 
	int d;
	int e;
}

int a;
int b;

void test()
{
	bite::a = 1;
	bite::bite_69::fun1;


}
void test2()//c++的输入输出
{
	int a = 1;
	int b;
	char d[10] = "loud";
	char* o = "1234";
	//*o = 3;

	std::cout << a << "\n";//假设头文件<iostream> + std命名空间;c++头文件没有“.h”
	//
	std::cin >> b >> a >> bite::a >> bite::bite_69::b;
	char* p = d;
	std::cout << p << std::endl;
	std::cout << o << std::endl;
}
//缺省值定义的时候，只可以在定义，或者声明阶段，而且只能俩个中的一个，否则编译器分不清楚
void fun(int a = 1, int b = 2, int c = 3)// *全缺省
//c++支持的默认参数哦“缺省参数”

//给定一个默认值，实际使用时候，如果没给传参，使用默认参数
{
	std::cout << a << b << c << std::endl;
}
void fun6(int a, int b = 3, int c = 4)
//半缺省，使用时必须传a，缺省参数必须从右向左依次连续赋值，中间不能有间隔；
{
	std::cout << a << b << c << std::endl;

}
//函数重载： 函数名想=相同，参数不同， 且在同一个作用域
//参数不同：类型，个数，顺序不同
//仅仅是返回值不同，不能构成重载
int Add(int a, int b)
{
	return a + b;
}

float Add(float a, float b)
{
	return a + b;

}
int Add(int a, int b, int c)
{
	return a + b + c;
}
int Add(char a, int b)
{
	return a + b;
}
int Add(int a, char b)
{
	return a + b;
}
void test4()
{
	int a = 1;
	int b = 2;
	float c = 1.5;
	float d = 2.5;
	char f = 'a';
	int e = 3;
	char g = 'b';
	int h = 4;
	Add(a, b);
	Add(c, d);
	Add(a, b, e);
	Add(f, e);
	Add(h, g);
}


//引用
//概念：起个名字，指向同一个东西
//引用：类型 + & + 引用名称
//引用时必须初始化,引用定义后，不会再去更改实体的指向
void test6()
{
	int a = 10;
	int& ra = a;
	int& ra2 = b;
	ra2 = 100;
	std::cout << &a << std::endl;
	std::cout << &ra << std::endl;
}
void test7()
{
	//const引用
	const int a = 10;
	const int& ra = a;
	const int& r = 10;
	double d = 2.0;
	double& rd = d;
	int c = d;//隐式类型转换，生成有个临时的整形变量，rd2指向的为此临时变量，临时变量具有常性
	const int& rd2 = d;//这里rd2是一个常量，放在代码段，是不可以进行修改的
}
int main()
{
	int a;
	int b;
	//test2();
	test4;
	//fun(1, 2, 3);
	//fun();
	//fun(100, 200, 300);
	//fun函数不存在第一个参数不传的情况，参数要连续的给，从第一个开始，
	return 0;
}

void fun1(int a)
{

}
void fun2(int& a)
{

}

void test1()
{
	int a = 2;
	int n = 1000000000;
	size_t begin = clock();
	for (int i = 0; i < n; ++i)
		fun1(a);
	size_t end = clock();
	std::cout << "fun1(int): " << end - begin << std::endl;

	begin = clock();
	for (int i = 0; i < n; ++i)
		fun2(a);
	end = clock();
	std::cout << "fun2(int&): " << end - begin << std::endl;

	begin = clock();
}
void test5()
{
	//新的循环语法
	//范围for： 要迭代的变量  ：（冒号） 迭代的范围
	int array[] = { 1, 2, 3, 4, 5, 6 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
	{
		std::cout << array[i] << " ";
		
	}std::cout << std::endl;
	for (auto e : array)
	{
		std::cout << e << " ";
		;
	}std::cout << std::endl;
}

void test8()
{
	int* p = NULL; //int* p = 0；
	int* p2 = 0;//和上面指令没有区别
}
void fun6(int)
{
	std::cout << "fun6(int)" << std::endl;
}
void fun6(int*)
{
	std::cout << "fun(int*)" << std::endl;
}
void test9()
{
	fun6(NULL);//编译器默认NULL为整形的0，而不是指针空值
	fun6((int*)NULL);//二义性，指针空值，整形0；
	fun6(nullptr);//指针空值，建议使用nullptr表示指针空值，意义明确
	//nullptr可以隐式转换为任意指针类型（内置和自定义）
	int* p = nullptr;
	char* q = nullptr;//类型：nullptr_t;
	std::cout << typeid(nullptr).name() << std::endl;
	std::cout << sizeof(nullptr) << std::endl;
}


struct Strudent
{
	void display()
	{
	}
	void setId(int id)
	{
	}
	char _number;
	int _id;
};
void test10()
{
	Strudent st;
	strcpy(st._number ,"12345")
}
int main()
{
	//test1();
	//test5();
	test9();
	return 0;
}
