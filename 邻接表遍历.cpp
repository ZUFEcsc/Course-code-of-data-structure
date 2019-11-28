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
 
//���ʱ�־������,Ϊ1��ʾ���ʹ���Ϊ0��ʾδ������
int visted[100];
//�߱���
typedef struct EdgeNode {
    //�����Ӧ���±�
    int adjvex;
    //ָ����һ���ڽӵ�
    struct EdgeNode *next;
} edgeNode;
 
//�������
typedef struct VertexNode {
    //��������
    char data;
    //�߱�ͷָ��
    edgeNode *firstedge;
} VertexNode, AdjList[100];
 
//����
typedef struct {
    AdjList adjList;
    //�������ͱ���
    int numVertexes, numEdges;
} GraphAdjList;

void CreateALGraph(GraphAdjList *G) {
    int i, j, k;
    edgeNode *e;
    cout << "���붥�����ͱ���" << endl;
    //���붥�����ͱ���
    cin >> G->numVertexes >> G->numEdges;
    //���붥����Ϣ�����������
    for (i = 0; i < G->numVertexes; i++)
    {
        //���붥����Ϣ
        cin >> G->adjList[i].data;
        //���߱���Ϊ�ձ�
        G->adjList[i].firstedge = NULL;
    }
    //�����߱�ͷ�巨��
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "����ߣ�vi,vj���ϵĶ������ :" ;
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
        cout << "����" << i << ": " << G->adjList[i].data << "--firstedge--";
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
            //�ݹ����
            DFS(G, p->adjvex);
        }
        p = p->next;
    }
 
}
 
void DFSTraverse(GraphAdjList *G) {
    //��ʼ�����ж��㶼û�з��ʹ�
    cout << "������ȱ������Ϊ��" ;
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
    cout << "������ȱ������Ϊ��";
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
