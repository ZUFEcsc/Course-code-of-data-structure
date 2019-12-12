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
void Kruskal(int n,int C[Vnum][Vnum])     //Kuruskral算法，顶点数n，带权临接矩阵V[n][n]
{
    int i,j;
    int nodeset[n];                       //顶点所属集合，之后用于判断顶点是否在同一暂时的树中
    int count=0;
    bool flag[n];                         //该数组用来判断顶点是否已经被选进生成树中
    for(i=0; i<n; i++)                    //将图中所有边存入数组边中
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
    sort(bian,bian+count,cmp);           /*将图中各边权值升序排列*/
    int edgeset=0;
    int w=0;                             /*用来存放生成树总权值*/
    count=0;
    while(edgeset<n-1)                   /*核心算法*/
    {
        if(!flag[bian[count].u] && flag[bian[count].v])   /*u未加入某一集合，v已经加入某个集合， 这个集合由已经找到的生成树顶点组成，开始可能形成多个*/
        {
            w+=bian[count].weight;
            flag[bian[count].u]=true;
            nodeset[bian[count].u]=nodeset[bian[count].v];
            edgeset++;
        }
        else if(flag[bian[count].u] && !flag[bian[count].v])/*v未加入，u已经加入*/
        {
            w+=bian[count].weight;
            flag[bian[count].v]=true;
            nodeset[bian[count].v]=nodeset[bian[count].u];
            edgeset++;
        }
        else if(!flag[bian[count].u] && !flag[bian[count].v])            /*两个都未加入*/
        {
            w+=bian[count].weight;
            flag[bian[count].u]=true;
            flag[bian[count].v]=true;
            nodeset[bian[count].u]=nodeset[bian[count].v];
            edgeset++;
        }
        else if(nodeset[bian[count].u]!=nodeset[bian[count].v])/*如果两个加入集合，判断加入集合是否相同，相同说明形成环，跳出此次循环，转向下一次。*/
        {                                                      /*否则将两个集合合并*/
            w+=bian[count].weight;
            edgeset++;
            int tmp=nodeset[bian[count].v];
            for(i=0;i<n;i++)
                if(nodeset[i]=tmp)
                nodeset[i]=nodeset[bian[count].u];
        }
        count++;                          /*转向次小边，进行下一次判断*/
    }
    cout<<"The weight of the minimum spanning tree is："<<w;              /*输出权值*/
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
测试数据：
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
