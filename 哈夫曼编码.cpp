#include <iostream>
#include <string>
 
using namespace std;
 
struct Node
{
	int lChild, rChild, parent;
	string code;
	int weight;
	string c;
};
 
//从当前叶节点和已经构造的节点中选出最小的两个数
void Select(Node nd[], int n, int& a, int &b)
{
	double wt = 0;
	for (int i = 0; i < n; ++i)
	{
		if (nd[i].parent != -1)
			continue;
		if (wt == 0 && nd[i].parent == -1)
		{
			wt = nd[i].weight;
			a = i;
		}
		else if (nd[i].parent == -1 && nd[i].weight < wt)
		{
			wt = nd[i].weight;
			a = i;
		}
	}
	wt = 0;
	for (int i = 0; i < n; ++i)
	{
		if (nd[i].parent != -1 || i == a)
			continue;
		if (wt == 0 && nd[i].parent == -1)
		{
			wt = nd[i].weight;
			b = i;
		}
		else if (nd[i].parent == -1 && nd[i].weight < wt)
		{
			wt = nd[i].weight;
			b = i;
		}
	}
}
 
//构造huffman树
void HuffTree(int w[], string ch[], int N, int M, Node nd[])
{
	//初始化Node数组
	for (int i = 0; i < M; ++i)
	{
		//-1代表没有
		nd[i].lChild = -1;
		nd[i].rChild = -1;
		nd[i].parent = -1;
		nd[i].code = "";
	}
	for (int i = 0; i < N; ++i)
	{
		nd[i].weight = w[i];
		nd[i].c = ch[i];
	}
 
	for (int i = N; i < M; ++i)
	{
		int a = 0, b = 0;
		Select(nd, i, a, b);
		nd[a].parent = i;
		nd[b].parent = i;
		nd[i].lChild = a;
		nd[i].rChild = b;
		nd[i].weight = nd[a].weight + nd[b].weight;
	}
}
 
void HuffEnCode(Node nd[], int N)
{
	int i, j, k;
	for (int i = 0; i < N; ++i)
	{
		string s = "";
		j = i;
		//从叶节点一直找到根节点
		while (nd[j].parent != -1)
		{
			k = nd[j].parent;
			if (nd[k].lChild == j)
			{
				s = s + "0";
			}
			else
			{
				s = s + "1";
			}
			j = k;
		}
		for (int x = s.size(); x >= 0; --x)
			nd[i].code += s[x];
		cout << nd[i].c << " の code: " << nd[i].code << endl;
	}
}
 
void HuffmanDecode(Node nd[], string str, int N, int M)
{
	string res = "";
	int i = 0, j = 0;
	int p = M - 1;
	while (i < str.size())
	{
		if (str[i] == '0')
			p = nd[p].lChild;
		if (str[i] == '1')
			p = nd[p].rChild;
		//找到了叶节点
		j = p;
		if (p < N)
		{
			res += nd[p].c;
			//重新回到叶节点
			p = M - 1;
		}
		++i;
	}
	if (j >= N)
		cout << "ERROR";
	else
		cout << res << endl;
}
 
int main()
{
	
	int wt[1000];
	string ch[1000];
	int n;
	cout<<"Please input character information (quantity) like 8:";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Please input the number & content of string as 10 A:"; 
		int w;
		string s;
		cin>>wt[i]>>ch[i];
	}
	Node nd[2000]; //n个叶节点构造的哈夫曼树的结点个数为2n - 1
	HuffTree(wt, ch, n, 2*n-1, nd);
	HuffEnCode(nd, n);
	//解码 
//	string str;
//	cin >> str;
//	HuffmanDecode(nd, str, n, 2*n-1);
}
