#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

#define maxn 110        //最大顶点个数
#define INF 0xffffff    //权值上限
int w[maxn][maxn];      //邻接矩阵，存储权值
int n;                  //顶点个数

struct node             //顶点节点，保存id和到源顶点的估算距离，优先队列需要的类型
{
    int id, weight;     //源顶点id和估算距离
    friend bool operator<(node a, node b)   //因要实现最小堆，按升序排列，因而需要重载运算符，重定义优先级，以小为先
    {
        return a.weight > b.weight;
    }
};
priority_queue<node> q;     //优先队列，最小堆，实现Dijkstra的重要数据结构，用stl实现
int parent[maxn];           //每个顶点的父亲节点，可以用于还原最短路径树
bool visited[maxn];         //用于判断顶点是否已经在最短路径树中，或者说是否已找到最短路径
node d[maxn];               //源点到每个顶点估算距离，最后结果为源点到所有顶点的最短路。
void Dijkstra(int s)        //Dijkstra算法，传入源顶点
{
    for(int i = 1; i <= n; i++)     //初始化
    {
        d[i].id = i;
        d[i].weight = INF;          //估算距离置INF
        parent[i] = -1;             //每个顶点都无父亲节点
        visited[i] = false;         
    }
    d[s].weight = 0;                //源点到源点最短路权值为0
    q.push(d[s]);                   //压入队列中
    while(!q.empty())               //算法的核心，队列空说明完成了操作
    {
        node cd = q.top();          //取最小估算距离顶点
        q.pop();
        int u = cd.id;
        if(visited[u])
            continue;
        visited[u] = true;
        //松弛操作
        for(int v = 1; v <= n; v++) //找所有与他相邻的顶点，进行松弛操作，更新估算距离，压入队列。
        {
            if(v != u && !visited[v] && d[v].weight > d[u].weight+w[u][v])
            {
                d[v].weight = d[u].weight+w[u][v];
                parent[v] = u;
                q.push(d[v]);
            }
        }
    }
}
int main()
{
    int m, a, b, c, st, ed;
    printf("ALL IS RIGHT ~\n");
    printf("Please enter the number of nodes & edges: ");
    scanf("%d %d", &n, &m);
    printf("Please enter the edge and weight: \n");
    for(int i = 1; i <= n; i++)     //邻接矩阵存储前需要初始化
        for(int j = i; j <= n; j++)
            w[i][j] = w[j][i] = INF;
    while(m--)
    {
        scanf("%d %d %d", &a, &b, &c);
        if(w[a][b] > c)
            w[a][b]= w[b][a] = c;
    }
    printf("Please enter start and end points:\n");
    scanf("%d %d", &st, &ed);
    Dijkstra(st);
    if(d[ed].weight != INF)
        printf("The shortest path weight is: %d\n", d[ed].weight);
    else
        printf("There is no shortest path from %d to %d.\n", st, ed);
    return 0;
}
/*
5 7 
1 2 2
1 4 6
2 4 5
2 3 8
3 4 4
3 5 6
4 5 1
1 5 
*/ 
