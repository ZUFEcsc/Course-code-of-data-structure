#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 65535 
typedef struct qstru{
		int x;
		int y;
		int pre;
}QElemType;

int flag=0;

typedef int Status;
 
typedef struct queue{
        QElemType *base;
        int front; //指示队头位置
        int rear;  //指示队尾位置
}SqQueue;
 
void initQueue(SqQueue *q){
	q->base = (QElemType*)malloc(SIZE*sizeof(QElemType));
	q->front=q->rear=0;
}
 
void enQueue(SqQueue *q,QElemType e){
		q->base[q->rear]=e;
		q->rear++;
}
 
void deQueue(SqQueue *q,QElemType *e){
		*e=q->base[q->front];
		q->front++;
}

void printq(SqQueue q,int pos){//输出迷宫路径 
	if(q.base[pos].pre!=-1)
	{
		flag=1;
		printq(q,q.base[pos].pre);
		flag=0;
	}
	
	if(flag==1)printf("( %d, %d)",q.base[pos].x,q.base[pos].y);
	else printf("-->( %d, %d)",q.base[pos].x,q.base[pos].y);
}
 
 
int **randomMap(int m,int n){//生成随机迷宫 
	srand((int)time(NULL));
	int **a,i,j;
	a=(int **)malloc(m*sizeof(int *));
	for( i=0;i<m;i++){
		a[i]=(int *)malloc(n*sizeof(int));
	}
	
	for( i=0;i<m;i++){
		for( j=0;j<n;j++){
		 	if(i==0||i==m-1||j==0||j==n-1)
				a[i][j]=1;
			else
				a[i][j]=rand()%2;
		}
		
	}
	a[1][1]=0,a[m-2][n-2]=0;
	return a; 
} 
void printMap(int **m,int a,int b){//输出迷宫地图 
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
}
int main(){
	SqQueue Q;
	int a,b,i,j;
	printf("输入迷宫的长和宽:");
	scanf("%d %d",&a,&b);
	int **m=randomMap(a+2,b+2);
	printMap(m,a+2,b+2);
 
 
	int delta[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}, {-1,0},{-1,1}}; 
 
 
	int end_x=a,end_y=b;
	initQueue(&Q);
	QElemType e,e1;
	e.pre=-1;	e.x=1;	e.y=1;
	
	enQueue(&Q,e);
	
	while(!(Q.front==Q.rear)){
	   int i,x,y;
	   deQueue(&Q,&e);
	   for(i=0;i<8;i++){
		   	x=e.x+delta[i][0];
		   	y=e.y+delta[i][1];
		   	
		   	if(m[x][y]==0){//如果可以走
		   		//形成新元素入队，标记走过-->2 
		   		e1.x=x;	e1.y=y;	e1.pre=Q.front-1;
		   		enQueue(&Q,e1);
		   		m[x][y]=2;
		   		if(x==end_x&&y==end_y){
		   		 printf("路径：\n");
		   		 printq(Q,Q.rear-1);return 0;
				}
			}
		   		
	   }
	}
	printf("无法通过!");
	return 0;
}
//8 9 
