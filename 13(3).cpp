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
	memset(L.data,0,sizeof(L));//初始化数据为0
	L.length=0;                //初始化长度为0
	return 0;
}
//创建顺序表函数 初始化前n个数据
bool CreatList(SqList &L,int n)
{
	if(n<0||n>MaxSize)false;//n非法
	for(int i=0;i<n;i++)
	{
		scanf("%d",&L.data[i]);
		L.length++;
	}
	return true;
}
//插入函数 位置i插入数据 i及之后元素后移  1=<i<=length+1 

//二分查找函数
int Binary_search(SqList L,ElemType key)
{
	int low = 0;int mid = 0;int high = L.length-1;
	while(low<=high)
	{
		mid = (low+high)/2;
 		if(key==L.data[mid])
		{
			return mid;
		}
		else if(key>L.data[mid])
		{
			low = mid+1;
		}
		else
		{
			high = mid-1;
		}
	}
	return -1;
}
//输出功能函数 按位置从小到大输出顺序表所有元素
void PrintList(SqList L)
{
	printf("All elements of the current sequence table :");
	for(int i=0;i<L.length;i++)
	{
		printf("%d ",L.data[i]);
	}
	printf("\n");
}
//创建顺序表函数
void Create(SqList &L)
{
	int n;bool flag;
	printf("Please enter the length of the order table to create(>1) :");
	scanf("%d",&n);
	printf("Please enter %d number (space separated):",n);
	flag=CreatList(L,n);
	if(flag){
		printf("Created successfully!\n");
		PrintList(L);
	}
	else printf("ILLEGAL INPUT!\n");
 
}
//简单选择排序功能函数 为二分做准备
void SelectSort(SqList &L)
{
	int min;int temp;
	for(int i=0;i<L.length;i++)
	{
		min=i;
		for(int j=i+1;j<L.length;j++)
		{
			if(L.data[j]<L.data[min])min=j;
		}			
		if(min!=i)
		{
			temp=L.data[min];
			L.data[min]=L.data[i];
			L.data[i]=temp;
		}
	}
}
//二分查找功能函数 调用Binary_search
void Binary(SqList L)
{
	int key;int place;
	SelectSort(L);       //二分查找前先排序
	PrintList(L);
	printf("Please enter the value to find ：\n");
	scanf("%d",&key);
	place=Binary_search(L,key);
	if(place>=0)printf("Index (from 0) is ：%d\n",place);
	else printf("NOT FOUND!\n");
}
int main()
{
	SqList L;int choice;
	InitList(L);
	Create(L);
	printf("START BINARY-FOUND  ↓↓\n"); 
	Binary(L);
	
	return 0;
}
//10
//18 5 27 13 57 36 9 6 62 77
//36
