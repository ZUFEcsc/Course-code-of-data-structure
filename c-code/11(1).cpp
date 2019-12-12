#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define NO 0
#define FALSE 0
#define TRUE 1
#define ERROR -1 

#define INFINITY 200000
#define MAX_VERTEX_NUM 20

typedef int *SetType;
typedef int Status;
typedef int VRType;//图、表顶点关系类型
typedef struct ArcCell
{
    VRType adj;  //权值
}ArcCell;

typedef ArcCell AdjMaxtrix[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1];//邻接矩阵
typedef char VertexType_M;//图的顶点类型


typedef struct 
{
    VertexType_M vexs[MAX_VERTEX_NUM+1];//顶点向量
    AdjMaxtrix arcs;
    int vexnum,arcnum;
}MGraph;

//作用非常的重要,主要是为了实现记录每一个结点的前一个结点以及它们之间的权重
typedef struct 
{
    VertexType_M adjvex;//较早加入当前边的端点
    VRType lowcost;//当前边的权值

}Edge;

typedef struct  //定义一个边集用来存储图的所有边信息
{
    int begin,end;
    int weight;
}gEdge;

Status visited[MAX_VERTEX_NUM+1];
Status CreateUDN_M(MGraph *G);
void OutputMGraph(MGraph G);
int LocateVex_M(MGraph G,VertexType_M u);
int MinSpanTree_PRIM(MGraph G,VertexType_M u);
int Minimum(Edge closedge[],int n);
void MinSpanTree_KRUSKAL(MGraph G);
gEdge *CreateEdges(MGraph G);//生成图的排序过的边集数组

int main(int argc,char** argv){
    MGraph G;
    printf("ALL IS RIGHT~\n");
        CreateUDN_M(&G);
		printf("Adjacency matrix information you entered :\n");
        OutputMGraph(G);
        printf("\n");
        int total;
        printf("Each node added to the tree and its corresponding weights are as follows :\n");
        total=MinSpanTree_PRIM(G,'A');
        printf("\n");
        printf("The value of minimum spanning tree is %d\n",total);
        printf("\n");
    return 0;
}
Status CreateUDN_M(MGraph *G){
    int i,j,k;
    VertexType_M v1,v2;
    VRType w;
    printf("Enter the number of vertices :");
    scanf("%d",&(G->vexnum));
    printf("Enter the number of edges :");
    scanf("%d",&(G->arcnum));
    printf("Enter values for each vertex & information of all edges:\n");
    getchar();
    for(i=1;i<=G->vexnum;i++)
    {
        scanf("%c ",&(G->vexs[i]));    
    }
    for(i=1;i<=G->vexnum;i++)
    {
        for(j=1;j<=G->vexnum;j++)
            G->arcs[i][j].adj=INFINITY;
    }
    for(k=1;k<=G->arcnum;k++)
    {
        getchar();
        scanf("%c %c %d",&v1,&v2,&w);
        i=LocateVex_M(*G,v1);
        j=LocateVex_M(*G,v2);
        
        G->arcs[i][j].adj=w;
        G->arcs[j][i]=G->arcs[i][j];
        }
return OK;
}

int LocateVex_M(MGraph G,VertexType_M u)
{
    int i;
    for(i=1;i<=G.vexnum;i++)
    {
        if(G.vexs[i]==u)
            return i;
    }
    return 0;
}

void OutputMGraph(MGraph G){
    int i,j;
    if(!G.vexnum&&!G.arcnum)
        printf("NULL\n");
    else
    {
        printf(" ");
        for(i=1;i<=G.vexnum;i++)
        {
            printf("%3c",G.vexs[i]);
        }
        printf("\n");
        for(i=1;i<=G.vexnum;i++)
        {
            printf("%c",G.vexs[i]);
            for(j=1;j<=G.vexnum;j++)
            {
                if(G.arcs[i][j].adj==INFINITY)
                    printf(" ∞");
                else
                    printf("%3d",G.arcs[i][j]);
            }
            printf("\n");
        }
    }
}

int MinSpanTree_PRIM(MGraph G,VertexType_M u){
    int i,j,k;
    int total=0;
    Edge closedge[G.vexnum+1];
    k=LocateVex_M(G,u);
    /*将辅助矩阵初始化使每一个结点都标记为前一个结点是u,并且它们之间的距离是无穷大，若是邻接点那么就是adj的值*/
    for(j=1;j<=G.vexnum;j++)
    {
        if(j!=k)
        {
            closedge[j].adjvex=u;  //标记j这个顶点的前一个顶点的信息
            closedge[j].lowcost=G.arcs[k][j].adj;
        }
    }
    closedge[k].lowcost=0; //自己到自己的cost标记为0
    printf("    %c\n", u);
    for(i=1;i<=G.vexnum-1;i++)//总共需要这么多此找出最小边
    {
        k=Minimum(closedge,G.vexnum);
        total+=closedge[k].lowcost;
        printf("%2d,%c\n",closedge[k].lowcost,G.vexs[k]);
        closedge[k].lowcost=0;
        for(j=1;j<=G.vexnum;j++)
        {
            if(G.arcs[k][j].adj<closedge[j].lowcost)
            {
                closedge[j].adjvex=G.vexs[k];
                closedge[j].lowcost=G.arcs[k][j].adj;
            }
        }
    }
    return total;
}

//找到所有和结点邻接的点中权值最小的并且返回j（用来标记最小的值所在的下标）
int Minimum(Edge closedge[],int n){
    int i,j;
    int min=INFINITY;
    i=1;
    j=0;
    for(;i<=n;i++){
        if(closedge[i].lowcost)//从权值不为0的边中选择拥有最小权值的边
        {
            if(closedge[i].lowcost<=min)
            {
                min=closedge[i].lowcost;
                j=i;
            }
        }
    }
    return j;
}

gEdge *CreateEdges(MGraph G){
    int i,j;
    int k=1;
    int EdgeNum=G.arcnum;
    int VertexNum=G.vexnum;
    gEdge temp;
    gEdge *p=(gEdge*)malloc(sizeof(gEdge)*VertexNum*VertexNum);   //之前程序报错 是因为申请的空间不够大，越界了
    
     for(i=1;i<=VertexNum;i++) //边集数组初始化
         for(j=i;j<=VertexNum;j++) //为了避免无向图的每条边被记录两次，只考虑上三角矩阵
             if(G.arcs[i][j].adj!=0&&G.arcs[i][j].adj!=INFINITY){
                 p[k].begin=i;
                 p[k].end=j;
                 p[k].weight=G.arcs[i][j].adj;
                 k++;
             }
            //首个p[i]与后面i+1……最后个依次比较，每一次都将小的放在第i个
    for(i=1;i<EdgeNum;i++)//对边集数组进行选择排序
        for(j=i+1;j<=EdgeNum;j++)
            if(p[i].weight>p[j].weight){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
    return p; //这个时候返回的p是已经从小到大排好序的，并且拥有一共EdgeNumt个大小的数组
}

/*
6
10
A B C D E F
A B 6
A C 1
A D 5
B C 5
B E 3
C D 5
C E 6
C F 4
D F 2
E F 6
*/
