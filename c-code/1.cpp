#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define MaxSize 100
#define ElemType int
#define Status int
using namespace std;
//顺序表数据结构
typedef struct
{
	ElemType data[MaxSize];//顺序表元素
	int length;            //顺序表当前长度
}SqList; 
//初始化顺序表函数，构造一个空的顺序表 
Status InitList(SqList &L)
{
	memset(L.data, 0, sizeof(L));//初始化数据为0
	L.length = 0;                //初始化长度为0
	return 0;
}
//创建顺序表函数 初始化前n个数据
bool CreatList(SqList &L, int n)
{
	if (n<0 || n>MaxSize)false;//n非法
	for (int i = 0; i<n; i++)
	{
		int temp;
		scanf("%d", &L.data[i]);
		L.length++;
	}
	return true;
}
//插入函数 位置i插入数据 i及之后元素后移  1=<i<=length+1 
bool InsertList(SqList &L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1) //判断位置是否有效
	{
		printf("ERROR！\n");
		return false;
	}
	if (L.length >= MaxSize)//判断存储空间是否已满
	{
		printf("The current storage space is full！\n");
		return false;
	}
	for (int j = L.length; j >= i; j--)//位置i及之后元素后移
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}
//删除函数 删除位置i的元素 i之后的元素依次前移
bool  ListDelete(SqList &L, int i)
{
	if (i<1 || i>L.length)
	{
		printf("ERROR！\n");
		return false;
	}
	for (int j = i; j <= L.length - 1; j++)//位置i之后元素依次前移覆盖
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}
//查找函数 按位置从小到大查找第一个值等于e的元素 并返回位置
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i<L.length; i++)//从低位置查找
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;
}
//输出功能函数 按位置从小到大输出顺序表所有元素
void PrintList(SqList L)
{
	printf("Now all numbers : ");
	for (int i = 0; i<L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
}
//创建顺序表函数
void Create(SqList &L)
{
	int n; bool flag;
	L.length = 0;
	printf("Please enter the length of the order table to create (> 1) : ");
	scanf("%d", &n);
	printf("Please enter %d number(s) : ", n);
	flag = CreatList(L, n);
	if (flag) {
		printf("OKay！\n");
		PrintList(L);
	}
	else printf("ERROR！\n");
 
}
//插入功能函数 调用InsertList完成顺序表元素插入 调用PrintList函数显示插入成功后的结果
void Insert(SqList &L)
{
	int place; ElemType e; bool flag;
	printf("Please enter the location (starting from 1) and element to insert :\n");
	scanf("%d %d", &place, &e);
	flag = InsertList(L, place, e);
	if (flag)
	{
		printf("OKay！\n");
		PrintList(L);
	}
}
//删除功能函数 调用ListDelete函数完成顺序表的删除 调用PrintList函数显示插入成功后的结果
void Delete(SqList &L)
{
	int place; bool flag;
	printf("Please enter the location to delete (starting from 1) : ");
	scanf("%d", &place);
	flag = ListDelete(L, place);
	if (flag)
	{
		printf("OKay！\n");
		PrintList(L);
	}
}
//查找功能函数 调用LocateElem查找元素
void Search(SqList L)
{
	ElemType e; int flag;
	printf("Please enter the value to find : ");
	scanf("%d", &e);
	flag = LocateElem(L, e);
	if (flag)
	{
		printf("The index of the element is : %d\n", flag);
	}
	else
		printf("NOT FOUND！\n");
}

int main()
{
	SqList L; int choice;
	InitList(L);
	Create(L);
	Insert(L);
	Delete(L);
	Search(L);
	return 0;
}
//4
//1 5 3 2
//2 6
//1
//2 
