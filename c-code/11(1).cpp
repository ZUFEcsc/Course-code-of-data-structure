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
typedef int VRType;//ͼ�������ϵ����
typedef struct ArcCell
{
    VRType adj;  //Ȩֵ
}ArcCell;

typedef ArcCell AdjMaxtrix[MAX_VERTEX_NUM+1][MAX_VERTEX_NUM+1];//�ڽӾ���
typedef char VertexType_M;//ͼ�Ķ�������


typedef struct 
{
    VertexType_M vexs[MAX_VERTEX_NUM+1];//��������
    AdjMaxtrix arcs;
    int vexnum,arcnum;
}MGraph;

//���÷ǳ�����Ҫ,��Ҫ��Ϊ��ʵ�ּ�¼ÿһ������ǰһ������Լ�����֮���Ȩ��
typedef struct 
{
    VertexType_M adjvex;//������뵱ǰ�ߵĶ˵�
    VRType lowcost;//��ǰ�ߵ�Ȩֵ

}Edge;

typedef struct  //����һ���߼������洢ͼ�����б���Ϣ
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
gEdge *CreateEdges(MGraph G);//����ͼ��������ı߼�����

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
                    printf(" ��");
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
    /*�����������ʼ��ʹÿһ����㶼���Ϊǰһ�������u,��������֮��ľ���������������ڽӵ���ô����adj��ֵ*/
    for(j=1;j<=G.vexnum;j++)
    {
        if(j!=k)
        {
            closedge[j].adjvex=u;  //���j��������ǰһ���������Ϣ
            closedge[j].lowcost=G.arcs[k][j].adj;
        }
    }
    closedge[k].lowcost=0; //�Լ����Լ���cost���Ϊ0
    printf("    %c\n", u);
    for(i=1;i<=G.vexnum-1;i++)//�ܹ���Ҫ��ô����ҳ���С��
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

//�ҵ����кͽ���ڽӵĵ���Ȩֵ��С�Ĳ��ҷ���j�����������С��ֵ���ڵ��±꣩
int Minimum(Edge closedge[],int n){
    int i,j;
    int min=INFINITY;
    i=1;
    j=0;
    for(;i<=n;i++){
        if(closedge[i].lowcost)//��Ȩֵ��Ϊ0�ı���ѡ��ӵ����СȨֵ�ı�
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
    gEdge *p=(gEdge*)malloc(sizeof(gEdge)*VertexNum*VertexNum);   //֮ǰ���򱨴� ����Ϊ����Ŀռ䲻����Խ����
    
     for(i=1;i<=VertexNum;i++) //�߼������ʼ��
         for(j=i;j<=VertexNum;j++) //Ϊ�˱�������ͼ��ÿ���߱���¼���Σ�ֻ���������Ǿ���
             if(G.arcs[i][j].adj!=0&&G.arcs[i][j].adj!=INFINITY){
                 p[k].begin=i;
                 p[k].end=j;
                 p[k].weight=G.arcs[i][j].adj;
                 k++;
             }
            //�׸�p[i]�����i+1�����������αȽϣ�ÿһ�ζ���С�ķ��ڵ�i��
    for(i=1;i<EdgeNum;i++)//�Ա߼��������ѡ������
        for(j=i+1;j<=EdgeNum;j++)
            if(p[i].weight>p[j].weight){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
    return p; //���ʱ�򷵻ص�p���Ѿ���С�����ź���ģ�����ӵ��һ��EdgeNumt����С������
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
