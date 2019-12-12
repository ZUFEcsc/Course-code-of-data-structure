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
        MinSpanTree_KRUSKAL(G);
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

void MinSpanTree_KRUSKAL(MGraph G){
     int VertexNum=G.vexnum;
     int EdgeNum=G.arcnum;
     gEdge *p=CreateEdges(G);//������
     int *index=(int*)malloc(sizeof(int)*VertexNum);
     //index ���飬��Ԫ��Ϊ��ͨ�����ı�ţ�index[i]=index[j]��ʾ���Ϊi,j�Ķ�����һ����ͨ������
     int *MSTEdge = (int *)malloc(sizeof(int)*VertexNum); //�����洢�Ѿ�ȷ����MST�ıߵı�Ź�VertexNum-1����
     int k=1;
     int WeightSum=0;
     int IndexBegin,IndexEnd;
     int i,j,n;
     for(i=1;i<=VertexNum;i++) //��ʼ�����е�index=-1;
         index[i]=-1;
    for(i=1;i<VertexNum;i++)
    {
        for(j=1;j<=EdgeNum;j++)
        {
            if(!(index[p[j].begin]>=0&&index[p[j].end]>=0&&index[p[j].begin]==index[p[j].end])){//�ҵ���ǰ��û�м��뵽ͬһ����ͨ����Ȩֵ��С�ı�
                MSTEdge[i]=j;   //��ÿһ����ͬ�Ļ����Ƹ�MSTEdge һ����VertexNum����
                if((index[p[j].begin]==-1)&&(index[p[j].end]==-1))
                    index[p[j].begin]=index[p[j].end]=i;//��������֮��ֱ����ͨ
                else if((index[p[j].begin]==-1)&&(index[p[j].end]>=0)){
                    index[p[j].begin]=i;
                    IndexEnd=index[p[j].end];
                    for(n=1;n<=VertexNum;n++)
                        if(index[n]==IndexEnd)
                            index[n]=i; }        
                else  if((index[p[j].end]==-1)&&(index[p[j].begin]>=0))
                {
                    index[p[j].end]=i;
                    IndexBegin=index[p[j].begin];
                    for(n=1;n<=VertexNum;n++)
                    {
                        if(index[n]==IndexBegin)
                            index[n]=i;
                    }

                }
                else   //Ҳ����������㶼��������ȥ�� ���ǻ�û����ͨ 
                {
                    IndexEnd=index[p[j].end];
                    IndexBegin=index[p[j].begin];
                    for(n=1;n<=VertexNum;n++)
                    {
                        if(index[n]==IndexBegin||index[n]==IndexEnd)
                            index[n]=i;
                    }

                }
                break;  
                //����ִ����һ��֮��ֱ������ѭ����i������һ���ߣ���j��Ȼ��0��ʼ����֮ǰ��ֵ���ı߲����ٽ�ȥ
                //����ܹ���֤��ȥ�ıߵ�һ�Σ��������µı��������������Ѿ���ͬһ�������е�Ԫ�أ�Ҳ�����ٽ�ȥ
            }
        }
    }
     printf("MTS's edges��\n");
     for(i=1;i<VertexNum;i++){
         printf("%c--%c\n",G.vexs[p[MSTEdge[i]].begin],G.vexs[p[MSTEdge[i]].end]);
         WeightSum+=p[MSTEdge[i]].weight;
     }
    printf("MST's value��%d\n",WeightSum);

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
