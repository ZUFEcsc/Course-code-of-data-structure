#include <iostream>
#include<stack>
#include<queue>

using namespace std;

typedef struct Node
{
	char data;
	struct Node *lchild, *rchild;
}Node;

//通过先序的方式创建树，#表示空节点
/*
                   A
               B      C
             D   E   F  #
           #  # # # #  # 
创建上面的树应输入应为  ABD##E##CF###
前序遍历：ABDECF
中序遍历：DBEAFC
后序遍历：DEBFCA
层次遍历：ABCDEF
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


//打印一个节点的数据
void visit(Node* node)
{
	if(node!=NULL)
		cout << node->data;
}

//递归-前序遍历，先访问跟节点，然后访问左节点，最后访问右节点，每一个节点都要准守这样的规则
void preTraversal(Node* root)
{
	//访问跟节点
	if (root != NULL)
	{
		visit(root);
		preTraversal(root->lchild);
		preTraversal(root->rchild);
	}

}

//递归-中序遍历，先访问跟左节点，然后访问中节点，最后访问右节点，每一个节点都要准守这样的规则
void midTraversal(Node* root)
{
	if (root != NULL)
	{
		midTraversal(root->lchild);
		visit(root);
		midTraversal(root->rchild);
	}
}

//递归-后序遍历，先访问左节点，然后访问右节点，最后访问根节点，每一个节点都要准守这样的规则
void postTraversal(Node* root)
{
	if (root != NULL)
	{
		postTraversal(root->lchild);
		postTraversal(root->rchild);
		visit(root);
	}
}

//树的层次遍历
//思想：使用队列queue。先将根节点入队列，循环判断当前队列不为空时，将头元素出队列并访问头元素，然后在将它的左节点和右节点入队列
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
	//创建上面的树应输入应为  ABD##E##CF###

	Node* root;
	creatTree(root);
	cout << "前序遍历:";
	preTraversal(root);
	cout << endl;

	cout << "中序遍历:";
	midTraversal(root);
	cout << endl;

	cout << "后序遍历:";
	postTraversal(root);
	cout << endl;

	cout << "层次遍历:";
	levelTraversal(root);
	cout << endl;
}

