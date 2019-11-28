//4 5
//A B C D
//2 3
//2 1
//0 3
//0 2
//0 1
#include <iostream>
#include <queue>
 
using namespace std;
 
//访问标志的数组,为1表示访问过，为0表示未被访问
int visted[100];
//边表结点
typedef struct EdgeNode {
    //顶点对应的下标
    int adjvex;
    //指向下一个邻接点
    struct EdgeNode *next;
} edgeNode;
 
//顶点表结点
typedef struct VertexNode {
    //顶点数据
    char data;
    //边表头指针
    edgeNode *firstedge;
} VertexNode, AdjList[100];
 
//集合
typedef struct {
    AdjList adjList;
    //顶点数和边数
    int numVertexes, numEdges;
} GraphAdjList;

void CreateALGraph(GraphAdjList *G) {
    int i, j, k;
    edgeNode *e;
    cout << "输入顶点数和边数" << endl;
    //输入顶点数和边数
    cin >> G->numVertexes >> G->numEdges;
    //读入顶点信息，建立顶点表
    for (i = 0; i < G->numVertexes; i++)
    {
        //输入顶点信息
        cin >> G->adjList[i].data;
        //将边表置为空表
        G->adjList[i].firstedge = NULL;
    }
    //建立边表（头插法）
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "输入边（vi,vj）上的顶点序号 :" ;
        cin >> i >> j;
        e = new EdgeNode;
        e->adjvex = j;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;
 
        e = new EdgeNode;
 
        e->adjvex = i;
        e->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e;
    }
}
 
void Test() {
    cout << "ALL IS OK." << endl;
}
 
void howALGraph(GraphAdjList *G) {
    for (int i = 0; i < G->numVertexes; i++)
    {
        cout << "顶点" << i << ": " << G->adjList[i].data << "--firstedge--";
        edgeNode *p = new edgeNode;
        p = G->adjList[i].firstedge;
        while (p)
        {
            cout << p->adjvex << "-->";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
 
}
 
void DFS(GraphAdjList *G, int i) {
    EdgeNode *p;
    visted[i] = 1;
    cout << G->adjList[i].data << "-->";
    p = G->adjList[i].firstedge;
    while (p)
    {
        if (!visted[p->adjvex])
        {
            //递归访问
            DFS(G, p->adjvex);
        }
        p = p->next;
    }
 
}
 
void DFSTraverse(GraphAdjList *G) {
    //初始化所有顶点都没有访问过
    cout << "深度优先遍历结果为：" ;
    for (int i = 0; i < G->numVertexes; i++)
    {
        visted[i] = 0;
    }
    for (int i = 0; i < G->numVertexes; i++)
    {
        if (visted[i] == 0)
        {
            DFS(G, i);
        }
    }
    cout << "NULL" << endl;
}
 
void BFSTraverse(GraphAdjList *G) {
 
    EdgeNode *p;
    queue<int> Q;
    for (int i = 0; i < G->numVertexes; i++)
    {
        visted[i] = 0;
    }
    cout << "广度优先遍历结果为：";
    for (int i = 0; i < G->numVertexes; i++)
    {
        if (visted[i] == 0)
        {
            visted[i] = 1;
            cout << G->adjList[i].data << "-->";
            Q.push(i);
            while (!Q.empty())
            {
                Q.front()=i;
                Q.pop();
                p = G->adjList[i].firstedge;
                while (p)
                {
                    if (visted[p->adjvex] == 0)
                    {
                        visted[p->adjvex] = 1;
                        cout << G->adjList[p->adjvex].data << "-->";
                        Q.push(p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
    cout << "NULL" << endl; 
}
 
 
int main() {
 
    GraphAdjList *GA = new GraphAdjList;
    Test();
    CreateALGraph(GA);
    BFSTraverse(GA);
    DFSTraverse(GA);
    
    return 0;
}
