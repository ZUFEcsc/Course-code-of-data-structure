#include <iostream>
#include<stack>
#include<queue>

using namespace std;

typedef struct Node
{
	char data;
	struct Node *lchild, *rchild;
}Node;

//ͨ������ķ�ʽ��������#��ʾ�սڵ�
/*
                   A
               B      C
             D   E   F  #
           #  # # # #  # 
�����������Ӧ����ӦΪ  ABD##E##CF###
ǰ�������ABDECF
���������DBEAFC
���������DEBFCA
��α�����ABCDEF
*/
void creatTree(Node* &root)
{
	char data;
	cin >> data;
	if (data == '#')
		root = NULL;
	else
	{
		root = new Node;
		root->data = data;
		creatTree(root->lchild);
		creatTree(root->rchild);
	}

}


//��ӡһ���ڵ������
void visit(Node* node)
{
	if(node!=NULL)
		cout << node->data;
}

//�ݹ�-ǰ��������ȷ��ʸ��ڵ㣬Ȼ�������ڵ㣬�������ҽڵ㣬ÿһ���ڵ㶼Ҫ׼�������Ĺ���
void preTraversal(Node* root)
{
	//���ʸ��ڵ�
	if (root != NULL)
	{
		visit(root);
		preTraversal(root->lchild);
		preTraversal(root->rchild);
	}

}

//�ݹ�-����������ȷ��ʸ���ڵ㣬Ȼ������нڵ㣬�������ҽڵ㣬ÿһ���ڵ㶼Ҫ׼�������Ĺ���
void midTraversal(Node* root)
{
	if (root != NULL)
	{
		midTraversal(root->lchild);
		visit(root);
		midTraversal(root->rchild);
	}
}

//�ݹ�-����������ȷ�����ڵ㣬Ȼ������ҽڵ㣬�����ʸ��ڵ㣬ÿһ���ڵ㶼Ҫ׼�������Ĺ���
void postTraversal(Node* root)
{
	if (root != NULL)
	{
		postTraversal(root->lchild);
		postTraversal(root->rchild);
		visit(root);
	}
}

//���Ĳ�α���
//˼�룺ʹ�ö���queue���Ƚ����ڵ�����У�ѭ���жϵ�ǰ���в�Ϊ��ʱ����ͷԪ�س����в�����ͷԪ�أ�Ȼ���ڽ�������ڵ���ҽڵ������
void levelTraversal(Node* root)
{
	queue<Node*> q;
	Node* p = root;
	q.push(p);
	while (q.empty() == false)
	{
		p = q.front();
		q.pop();
		visit(p);
		if (p->lchild != NULL)
			q.push(p->lchild);
		if (p->rchild != NULL)
			q.push(p->rchild);
	}
}

int main()
{
	//�����������Ӧ����ӦΪ  ABD##E##CF###

	Node* root;
	creatTree(root);
	cout << "ǰ�����:";
	preTraversal(root);
	cout << endl;

	cout << "�������:";
	midTraversal(root);
	cout << endl;

	cout << "�������:";
	postTraversal(root);
	cout << endl;

	cout << "��α���:";
	levelTraversal(root);
	cout << endl;
}

