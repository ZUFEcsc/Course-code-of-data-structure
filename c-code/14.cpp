#include<bits/stdc++.h>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}Node;
//12
//12 24 48 13 26 14 15 16 17 19 20 21
//24 
int a[1010] = {0};
Node b[1010];
int n;

int f(int x)
{
	return x%n;
}

void Build()
{
	cout<<"Input n : ";
	cin>>n;
	cout<<"Input numbers in turn:";
	for(int i = 0;i < n;i++)
	{
		cin>>a[i];
	}
	for(int i = 0;i < n;i++)
	{
		b[i].next = NULL;
	}
	for(int i = 0;i < n;i++)
	{
		int x = f(a[i]);
		Node * newnode = (Node*)malloc(sizeof(Node));
		newnode->data = a[i];
		newnode->next = b[x].next;
		b[x].next = newnode;
	}
}

void Display()
{
	cout<<"HASH TABLE £º"<<endl;
	for(int i = 0;i < 12;i++)
	{
		cout<<i<<":  ";
		Node *s = b[i].next;
		while(s!=NULL)
		{
			cout<<s->data<<" ";
			s = s->next;
		}
		cout<<endl;
	}
}

void Find()
{
	int x;
	cout<<"Please enter the number to find : ";
	cin>>x;
	int y = f(x);
	Node * s = b[y].next;
	int num = 1;
	while(s)
	{
		if(s->data == x)
		{
			cout<<"EXISTENT ~"<<endl;
			cout<<"On line "<<y<<"£¬no."<<num<<endl;
			return;
		}
		num++;
		s = s->next;
	}
	cout<<"NON-EXISTENT !";
}

int main()
{
	Build();
	Display();
	Find();
}
