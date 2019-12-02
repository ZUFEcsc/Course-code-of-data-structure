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
//˳������ݽṹ
typedef struct
{
	ElemType data[MaxSize];//˳���Ԫ��
	int length;            //˳���ǰ����
}SqList;
//��ʼ��˳�����������һ���յ�˳��� 
Status InitList(SqList &L)
{
	memset(L.data,0,sizeof(L));//��ʼ������Ϊ0
	L.length=0;                //��ʼ������Ϊ0
	return 0;
}
//����˳����� ��ʼ��ǰn������
bool CreatList(SqList &L,int n)
{
	if(n<0||n>MaxSize)false;//n�Ƿ�
	for(int i=0;i<n;i++)
	{
		scanf("%d",&L.data[i]);
		L.length++;
	}
	return true;
}
//���뺯�� λ��i�������� i��֮��Ԫ�غ���  1=<i<=length+1 

//���ֲ��Һ���
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
//������ܺ��� ��λ�ô�С�������˳�������Ԫ��
void PrintList(SqList L)
{
	printf("All elements of the current sequence table :");
	for(int i=0;i<L.length;i++)
	{
		printf("%d ",L.data[i]);
	}
	printf("\n");
}
//����˳�����
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
//��ѡ�������ܺ��� Ϊ������׼��
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
//���ֲ��ҹ��ܺ��� ����Binary_search
void Binary(SqList L)
{
	int key;int place;
	SelectSort(L);       //���ֲ���ǰ������
	PrintList(L);
	printf("Please enter the value to find ��\n");
	scanf("%d",&key);
	place=Binary_search(L,key);
	if(place>=0)printf("Index (from 0) is ��%d\n",place);
	else printf("NOT FOUND!\n");
}
int main()
{
	SqList L;int choice;
	InitList(L);
	Create(L);
	printf("START BINARY-FOUND  ����\n"); 
	Binary(L);
	
	return 0;
}
//10
//18 5 27 13 57 36 9 6 62 77
//36
