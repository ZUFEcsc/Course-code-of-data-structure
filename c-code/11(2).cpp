#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
 
#define maxn 110  //��󶥵����
int n, m;       //������������
 
struct arcnode  //�߽��
{
    int vertex;     //���ͷ������ڵĶ�����
    int weight;     //����������ıߵ�Ȩֵ
    arcnode * next; //ָ����һ���ڽӵ�
    arcnode() {}
    arcnode(int v,int w):vertex(v),weight(w),next(NULL) {}
};
 
struct vernode      //�����㣬Ϊÿһ���ڽӱ�ı�ͷ���
{
    int vex;    //��ǰ������
    arcnode * firarc;   //��ö��������ĵ�һ��������ɵı�
}Ver[maxn];
 
void Init()  //����ͼ���ڽӱ���Ҫ�ȳ�ʼ��������������
{
    for(int i = 1; i <= n; i++)
    {
        Ver[i].vex = i;
        Ver[i].firarc = NULL;
    }
}
 
void Insert(int a, int b, int w)  //β�巨��������aΪ��㣬bΪ�յ㣬ȨΪw�ıߣ�Ч�ʲ���ͷ�壬���ǿ���ȥ�ر�
{
    arcnode * q = new arcnode(b, w);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        if(p->vertex == b)
        {
            if(p->weight > w)
                p->weight = w;
            return ;
        }
        while(p->next != NULL)
        {
            if(p->next->vertex == b)
            {
                if(p->next->weight > w);
                    p->next->weight = w;
                return ;
            }
            p = p->next;
        }
        p->next = q;
    }
}
void Insert2(int a, int b, int w)   //ͷ�巨��Ч�ʸ��ߣ�������ȥ�ر�
{
    arcnode * q = new arcnode(b, w);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        q->next = p;
        Ver[a].firarc = q;
    }
}
struct node     //����keyֵ�Ľ��
{
    int v;
    int key;
    friend bool operator<(node a, node b)   //�Զ������ȼ���keyС������
    {
        return a.key > b.key;
    }
};
 
#define INF 0xfffff    //Ȩֵ����
int parent[maxn];   //ÿ�����ĸ��ڵ�
bool visited[maxn]; //�Ƿ��Ѿ���������
node vx[maxn];      //����ÿ��������丸�ڵ����ӱߵ�Ȩֵ
priority_queue<node> q; //���ȶ���stlʵ��
void Prim()    //s��ʾ�����
{
    for(int i = 1; i <= n; i++) //��ʼ��
    {
        vx[i].v = i;
        vx[i].key = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    vx[1].key = 0;
    q.push(vx[1]);
    while(!q.empty())
    {
        node nd = q.top();  //ȡ���ף��ǵøϽ�pop��
        q.pop();
        if(visited[nd.v])   //ע����һ������⣬����ܶ಻��Ҫ�Ĳ���
            continue;
        visited[nd.v] = true;
        arcnode * p = Ver[nd.v].firarc;
        while(p != NULL)    //�ҵ��������ڽ�㣬��δ���ʣ��������
        {
            if(!visited[p->vertex] && p->weight < vx[p->vertex].key)
            {
                parent[p->vertex] = nd.v;
                vx[p->vertex].key = p->weight;
                vx[p->vertex].v = p->vertex;
                q.push(vx[p->vertex]);
            }
            p = p->next;
        }
    }
}
 
int main()
{
    int a, b ,w;
    cout << "Enter the number of nodes & edges: ";
    cin >> n >> m;
    Init();
    cout << "Enter all edge information :" << endl;
    while(m--)
    {
        cin >> a >> b >> w;
        Insert2(a, b, w);
    }
    Prim();
    cout << "Output the parent nodes of all nodes :" << endl;
    for(int i = 1; i <= n; i++)
        cout << parent[i] << " ";
    cout << endl;
    cout << "The weight of the minimum spanning tree is ��";
    int cnt = 0;
    for(int i = 1; i <= n; i++)
        cnt += vx[i].key;
    cout << cnt << endl;
    return 0;
}
/*
6 10
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 5 6
3 6 4
5 6 6
4 6 2
*/
