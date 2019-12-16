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
	memset(L.data, 0, sizeof(L));//��ʼ������Ϊ0
	L.length = 0;                //��ʼ������Ϊ0
	return 0;
}
//����˳����� ��ʼ��ǰn������
bool CreatList(SqList &L, int n)
{
	if (n<0 || n>MaxSize)false;//n�Ƿ�
	for (int i = 0; i<n; i++)
	{
		int temp;
		scanf("%d", &L.data[i]);
		L.length++;
	}
	return true;
}
//���뺯�� λ��i�������� i��֮��Ԫ�غ���  1=<i<=length+1 
bool InsertList(SqList &L, int i, ElemType e)
{
	if (i<1 || i>L.length + 1) //�ж�λ���Ƿ���Ч
	{
		printf("ERROR��\n");
		return false;
	}
	if (L.length >= MaxSize)//�жϴ洢�ռ��Ƿ�����
	{
		printf("The current storage space is full��\n");
		return false;
	}
	for (int j = L.length; j >= i; j--)//λ��i��֮��Ԫ�غ���
	{
		L.data[j] = L.data[j - 1];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}
//ɾ������ ɾ��λ��i��Ԫ�� i֮���Ԫ������ǰ��
bool  ListDelete(SqList &L, int i)
{
	if (i<1 || i>L.length)
	{
		printf("ERROR��\n");
		return false;
	}
	for (int j = i; j <= L.length - 1; j++)//λ��i֮��Ԫ������ǰ�Ƹ���
	{
		L.data[j - 1] = L.data[j];
	}
	L.length--;
	return true;
}
//���Һ��� ��λ�ô�С������ҵ�һ��ֵ����e��Ԫ�� ������λ��
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i<L.length; i++)//�ӵ�λ�ò���
	{
		if (L.data[i] == e)
			return i + 1;
	}
	return 0;
}
//������ܺ��� ��λ�ô�С�������˳�������Ԫ��
void PrintList(SqList L)
{
	printf("Now all numbers : ");
	for (int i = 0; i<L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
}
//����˳�����
void Create(SqList &L)
{
	int n; bool flag;
	L.length = 0;
	printf("Please enter the length of the order table to create (> 1) : ");
	scanf("%d", &n);
	printf("Please enter %d number(s) : ", n);
	flag = CreatList(L, n);
	if (flag) {
		printf("OKay��\n");
		PrintList(L);
	}
	else printf("ERROR��\n");
 
}
//���빦�ܺ��� ����InsertList���˳���Ԫ�ز��� ����PrintList������ʾ����ɹ���Ľ��
void Insert(SqList &L)
{
	int place; ElemType e; bool flag;
	printf("Please enter the location (starting from 1) and element to insert :\n");
	scanf("%d %d", &place, &e);
	flag = InsertList(L, place, e);
	if (flag)
	{
		printf("OKay��\n");
		PrintList(L);
	}
}
//ɾ�����ܺ��� ����ListDelete�������˳����ɾ�� ����PrintList������ʾ����ɹ���Ľ��
void Delete(SqList &L)
{
	int place; bool flag;
	printf("Please enter the location to delete (starting from 1) : ");
	scanf("%d", &place);
	flag = ListDelete(L, place);
	if (flag)
	{
		printf("OKay��\n");
		PrintList(L);
	}
}
//���ҹ��ܺ��� ����LocateElem����Ԫ��
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
		printf("NOT FOUND��\n");
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
