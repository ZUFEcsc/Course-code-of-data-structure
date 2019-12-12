#include <stdio.h>
#include <stdlib.h>
 
#define ERROR 1
#define OK 	  0
typedef struct LNode
{
	int data;		
	struct LNode *next; 
}LNode;

LNode *CreateList(int len)
{
	LNode *L = (LNode*)malloc(sizeof(LNode)); 
	LNode *temp = L;
	temp->next = NULL;
	for(int i=1;i<=len;i++) 
	{
		LNode *p = (LNode*)malloc(sizeof(LNode)); 
		scanf("%d",&p->data); 
		temp->next = p;   
		temp = p;		
	}
	temp->next = NULL;
	
	return (LNode*)L;
}
 
int Serch(LNode *L, int elem)
{
	LNode *temp = L;
	int pos = 0;
	int i = 1;
	while(temp->next)
	{
		temp = temp->next;
		if(elem==temp->data)
		{
			pos = i;
			printf("The index of this number is %d\n",pos);
			return pos;	
		}
		i++;
	}
	printf("Serch error!\n");
	
	return ERROR;
}

LNode *Replace(LNode *L, int pos, int elem)
{
	LNode *temp = L;
	temp = temp->next;
	for(int i=1;i<pos;i++)
	{
		temp = temp->next;
	}
	temp->data = elem;  
	return (LNode*)L;   
}
 
LNode *Insert(LNode *L, int pos, int elem)
{
	LNode *temp = L;
	int i = 0;
	while( (temp!=NULL)&&(i<pos-1) )
	{
		temp = temp->next;
		++i;
	}
	if( (temp==NULL)||(i>pos-1) )		
	{
		printf("ERROR!\n");
		return (LNode*)temp;
	}
	LNode *newl = (LNode*)malloc(sizeof(LNode));	
	newl->data = elem;	
	newl->next = temp->next; 
	temp->next = newl;	
	
	return (LNode*)L;
}
 
LNode *Delete(LNode *L, int pos, int *elem)
{
	LNode *temp = L;
	int i = 0;
	while( (temp!=NULL)&&(i<pos-1) )
	{
		temp = temp->next;
		++i;
	}
	if( (temp==NULL)||(i>pos-1) )
	{
		printf("ERROR!\n");
		return (LNode*)temp;
	}
	LNode *del = temp->next;
	*elem = del->data;		
	temp->next = del->next;	
	free(del);		
	del = NULL;			
	
	return (LNode*)L;		
}
 
void PrintfList(LNode *L)
{
	LNode *temp = L;
	int count = 0;
	printf("List:\n");
	while(temp->next)
	{
		temp = temp->next;
		printf("%d ,",temp->data);
		count++;
	}
	printf("\n");
}
 
int MenuSelect(void)
{
	int cmd;
	printf("1.Serch test\n");
	printf("2.Replace test\n");
	printf("3.Insert test\n");
	printf("4.Delete test\n");
	do
	{
		printf("Enter your choice: ");
		scanf("%d",&cmd);
	}while(cmd<0||cmd>4);
	return cmd;
}

void Test1(LNode *L)	
{
	int serchElem = 0;		
	printf("--start--\n");
	PrintfList(L);
	printf("Input the element you want to serch:");
	scanf("%d",&serchElem);
	Serch(L,serchElem);
	printf("--end--\n");
	printf("\n");
}
 
void Test2(LNode *L)	
{
	int replacePos = 0, replaceElem = 0; 
	printf("--start--\n");
	PrintfList(L);
	printf("Input the position and the element you want to replace(example:10,33):");
	scanf("%d,%d",&replacePos,&replaceElem);
	L = Replace(L,replacePos,replaceElem);
	printf("After replace,list is:\n");
	PrintfList(L);
	printf("--end--\n");
	printf("\n");
}
 
void Test3(LNode *L)	
{
	int insertPos = 0, insertElem = 0;
	
	printf("--start--\n");
	PrintfList(L);
	printf("Input the position and the element you want insert(example:10,33):");
	scanf("%d,%d",&insertPos,&insertElem);
	L = Insert(L,insertPos,insertElem);
	printf("After insert,list is:\n");
	PrintfList(L);
	printf("--end--\n");
	printf("\n");
}
 
void Test4(LNode *L)	
{
	int deletePos = 0;
	int elem = NULL;
	
	printf("--start--\n");
	PrintfList(L);
	printf("Input the position of the element you want to delete(example:10):");
	scanf("%d",&deletePos);
	L = Delete(L,deletePos,&elem);
	printf("After delete,list is:\n");
	PrintfList(L);
	printf("--end--\n");
	printf("\n");
}
 
int main(void)
{
	int len = 0;
	int cmd;
	LNode *L;		
	
	printf("Please input list length:");
	scanf("%d",&len);
	L = CreateList(len);
	PrintfList(L);
	while(1)
	{
		cmd = MenuSelect();
		switch(cmd)
		{
			case 1: Test1(L);		break;
			case 2: Test2(L);		break; 
			case 3: Test3(L);		break; 
			case 4: Test4(L);		break; 
		}
	}
	return 0;
}

