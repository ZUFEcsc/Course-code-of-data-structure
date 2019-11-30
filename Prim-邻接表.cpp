#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
 
#define maxn 110  //最大顶点个数
int n, m;       //顶点数，边数
 
struct arcnode  //边结点
{
    int vertex;     //与表头结点相邻的顶点编号
    int weight;     //连接两顶点的边的权值
    arcnode * next; //指向下一相邻接点
    arcnode() {}
    arcnode(int v,int w):vertex(v),weight(w),next(NULL) {}
};
 
struct vernode      //顶点结点，为每一条邻接表的表头结点
{
    int vex;    //当前定点编号
    arcnode * firarc;   //与该顶点相连的第一个顶点组成的边
}Ver[maxn];
 
void Init()  //建立图的邻接表需要先初始化，建立顶点结点
{
    for(int i = 1; i <= n; i++)
    {
        Ver[i].vex = i;
        Ver[i].firarc = NULL;
    }
}
 
void Insert(int a, int b, int w)  //尾插法，插入以a为起点，b为终点，权为w的边，效率不如头插，但是可以去重边
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
void Insert2(int a, int b, int w)   //头插法，效率更高，但不能去重边
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
struct node     //保存key值的结点
{
    int v;
    int key;
    friend bool operator<(node a, node b)   //自定义优先级，key小的优先
    {
        return a.key > b.key;
    }
};
 
#define INF 0xfffff    //权值上限
int parent[maxn];   //每个结点的父节点
bool visited[maxn]; //是否已经加入树种
node vx[maxn];      //保存每个结点与其父节点连接边的权值
priority_queue<node> q; //优先队列stl实现
void Prim()    //s表示根结点
{
    for(int i = 1; i <= n; i++) //初始化
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
        node nd = q.top();  //取队首，记得赶紧pop掉
        q.pop();
        if(visited[nd.v])   //注意这一句的深意，避免很多不必要的操作
            continue;
        visited[nd.v] = true;
        arcnode * p = Ver[nd.v].firarc;
        while(p != NULL)    //找到所有相邻结点，若未访问，则入队列
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
    cout << "The weight of the minimum spanning tree is ：";
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
