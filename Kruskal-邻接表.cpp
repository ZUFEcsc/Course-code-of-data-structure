#include<iostream>
#define Vnum 10
#define MAX 10000
#include<string.h>
#include<algorithm>
using namespace std;
typedef char Datatype;
typedef struct arcnode
{
    int adjvex;
    int weight;
    struct arcnode *nextarc;
} arcnode;
typedef struct
{
    Datatype vexdata;
    arcnode *firstarc;
} Adjlist;
typedef struct
{
    int arcnum,vexnum;
    Adjlist adjlist[Vnum];
} GraphTp;
int visit[Vnum];
int quan[Vnum][Vnum];
void creat(GraphTp *g)
{
    int i,j,k,ii,quanz;
    char tailarc,headarc;
    arcnode *p;
    cout<<"enter vexnum and arcnum:";
    cin>>g->vexnum>>g->arcnum;
    cout<<"enter the vexdata:";
    for(i=0; i<g->vexnum; i++)
    {
        cin>>g->adjlist[i].vexdata;
        g->adjlist[i].firstarc=NULL;
    }
    cout<<"enter the arcdata:"<<endl;
    for(ii=0; ii<g->arcnum; ii++)
    {
        cin>>tailarc>>headarc>>quanz;
        for(k=0; k<g->vexnum; k++)
            if(g->adjlist[k].vexdata==tailarc)
            {
                i=k;
                break;
            }
        for(k=0; k<g->vexnum; k++)
            if(g->adjlist[k].vexdata==headarc)
            {
                j=k;
                break;
            }
        p=new arcnode;
        p->adjvex=j;
        p->weight=quanz;
        quan[i][j]=quanz;
        quan[j][i]=quanz;
//        cout<<"the data is:"<<i<<' '<<j<<' '<<quanz<<endl;
        p->nextarc=g->adjlist[i].firstarc;
        g->adjlist[i].firstarc=p;
    }
}
struct edge
{
    int weight;
    int u,v;
} bian[Vnum];
int cmp(edge A,edge B)
{
    return A.weight<B.weight;
}
void Kruskal(int n,int C[Vnum][Vnum])     //Kuruskral�㷨��������n����Ȩ�ٽӾ���V[n][n]
{
    int i,j;
    int nodeset[n];                       //�����������ϣ�֮�������ж϶����Ƿ���ͬһ��ʱ������
    int count=0;
    bool flag[n];                         //�����������ж϶����Ƿ��Ѿ���ѡ����������
    for(i=0; i<n; i++)                    //��ͼ�����бߴ����������
    {
        nodeset[i]=i;
        flag[i]=false;
        for(j=0; j<n; j++)
            if(C[i][j]<MAX)
            {
                bian[count].u=i;
                bian[count].v=j;
                bian[count].weight=C[i][j];
                count++;
            }
    }
    sort(bian,bian+count,cmp);           /*��ͼ�и���Ȩֵ��������*/
    int edgeset=0;
    int w=0;                             /*���������������Ȩֵ*/
    count=0;
    while(edgeset<n-1)                   /*�����㷨*/
    {
        if(!flag[bian[count].u] && flag[bian[count].v])   /*uδ����ĳһ���ϣ�v�Ѿ�����ĳ�����ϣ� ����������Ѿ��ҵ���������������ɣ���ʼ�����γɶ��*/
        {
            w+=bian[count].weight;
            flag[bian[count].u]=true;
            nodeset[bian[count].u]=nodeset[bian[count].v];
            edgeset++;
        }
        else if(flag[bian[count].u] && !flag[bian[count].v])/*vδ���룬u�Ѿ�����*/
        {
            w+=bian[count].weight;
            flag[bian[count].v]=true;
            nodeset[bian[count].v]=nodeset[bian[count].u];
            edgeset++;
        }
        else if(!flag[bian[count].u] && !flag[bian[count].v])            /*������δ����*/
        {
            w+=bian[count].weight;
            flag[bian[count].u]=true;
            flag[bian[count].v]=true;
            nodeset[bian[count].u]=nodeset[bian[count].v];
            edgeset++;
        }
        else if(nodeset[bian[count].u]!=nodeset[bian[count].v])/*����������뼯�ϣ��жϼ��뼯���Ƿ���ͬ����ͬ˵���γɻ��������˴�ѭ����ת����һ�Ρ�*/
        {                                                      /*�����������Ϻϲ�*/
            w+=bian[count].weight;
            edgeset++;
            int tmp=nodeset[bian[count].v];
            for(i=0;i<n;i++)
                if(nodeset[i]=tmp)
                nodeset[i]=nodeset[bian[count].u];
        }
        count++;                          /*ת���С�ߣ�������һ���ж�*/
    }
    cout<<"The weight of the minimum spanning tree is��"<<w;              /*���Ȩֵ*/
}
int main()
{
    int i,j;
    for(i=0; i<Vnum; i++)
        for(j=0; j<Vnum; j++)
            quan[i][j]=MAX;
    GraphTp g;
    creat(&g);
    cout<<endl;
    Kruskal(g.vexnum,quan);
    return 0;
}
/*
�������ݣ�
6 10
0 1 2 3 4 5
0 1 6
0 2 1
0 3 5
1 2 5
1 4 3
2 3 5
2 4 6
2 5 4
4 5 6
3 5 2
*/
