#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
void InsertSort(int a[], int n)
{
    int i, j;
    for(i=1; i<n; i++)
        if(a[i] < a[i-1])   
        {
            int temp = a[i];                       //����Ҫ�Ƚϵ�ֵ
            for(j=i-1; j>=0 && a[j]>temp; j--)    //�Ӻ���ǰ���Ҵ�����λ��
                a[j+1] = a[j];                    //Ųλ
            a[j+1] = temp;                       //���Ƶ�����λ��
        }
}

void Swap(int a,int b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}
 
void shellSort(int a[],int n){
    int i,j,gap,temp;
    for(gap = n/2;gap>0;gap/=2){
        for(i=gap;i<n;i+=gap){
            temp = a[i];
            for(j = i-gap;j>=0&&a[j]>temp;j-=gap){
                a[j+gap] = a[j];
            }
            a[j+gap] = temp;
        }
    }
}

void BubbleSort(int a[], int n)
{
    int i, j;
    for(i=0; i<n; i++){
        bool flag=false;              //��ʾ����ð���Ƿ��������ı�־
        for(j=1; j<n-i; j++){         //j����ʼλ��Ϊ1����ֹλ��Ϊn-i  
            if(a[j]<a[j-1]){
               Swap(a[j-1], a[j]);
                flag=true;
            }
        }
        if(flag==false)             //δ������˵���Ѿ�����ֹͣ����
            return;
    }          
}
 
void QuickSort(int a[],int left,int right){
    if(left<right){
        int i=left,j=right;
        int base=a[left];             //��׼
        while(i<j){
            while(i<j&&a[j]>=base)    //����������С��base��Ԫ��
                j--;
            if(i<j)
                a[i++]=a[j];
            while(i<j&&a[i]<base)    //���������Ҵ���base��ֵ
                i++;
            if(i<j)
                a[j--]=a[i];
        }
        a[i]=base;                  //����׼base�������Ŀ���
        QuickSort(a,left,i-1);      //�ݹ���ã�����
        QuickSort(a,i+1,right);
    }
} 

void SelectSort(int a[],int n){
    int i,j,min;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            if(a[j]<a[min])
                      min=j;
        }
        if(min!=i)
		   Swap(a[i],a[min]); 
    }
}
 
void Merge(int A[], int Temp[], int L, int R, int RightEnd){
    int LeftEnd = R-1;
    int p=L,i;
    int num=RightEnd-L+1;
 
    //�Ⱥϲ�������еĳ��ȵĸ�����Ԫ��
    while(L<=LeftEnd&&R<=RightEnd){
 
        if(A[L]<=A[R])
            Temp[p++]=A[L++];
        else
            Temp[p++]=A[R++];
    }
 
    //�ж������������л���ʣ��
    while(L<=LeftEnd)
        Temp[p++]=A[L++];
    //�ж�������Ҳ����л���ʣ��
    while(R<=RightEnd)
        Temp[p++]=A[R++];
    // �������ռ��е�ֵ������ԭ�б��У��������
    for(i=0;i<num;i++,RightEnd--)
        A[RightEnd]=Temp[RightEnd];
} 
 
//�ݹ��֣��ݹ�鲢
void m_sort(int* arr, int* temp, int L, int right_end){
    int center;
    if(L<right_end){
        center = (L+right_end)/2;
        m_sort(arr,temp,L,center);
        m_sort(arr,temp,center+1,right_end);
        Merge(arr,temp,L,center+1,right_end);
    }
}

//�鲢����
void merge_Sort(int* arr,int length){
    int *temp=(int* )malloc(length*sizeof(int));  //���븨���ռ�
    if(temp==NULL){
        return;
    }
    m_sort(arr,temp,0,length-1);
    free(temp);
    temp=NULL;
}
 
//��ӡԪ��
void printArr(int *arr,int length){
    for(int i=0;i<length;i++){
        printf("%d  ",arr[i]);
    }
    printf("\n");
}
 
int main(){
    int arr[10]={32,53,24,106,82,93,76,84,79,91};
    int length = sizeof(arr)/sizeof(int);
    length = 10;   
    printf("BEFORE SORT : ");
    printArr(arr,length);
    
    merge_Sort(arr,length);
	printf("MERGE SORT  : ");  
    printArr(arr,length);
    
	SelectSort(arr,length);
    printf("SELECT SORT : ");
    printArr(arr,length);
    
    BubbleSort(arr,length); 
    printf("BUBBLE SORT : ");   
    printArr(arr,length);
    
    QuickSort(arr,0,length-1);
    printf("QUICK SORT  : ");
    printArr(arr,length);
    
    shellSort(arr,length);
    printf("SHELL SORT  : ");
	printArr(arr,length);
	
    InsertSort(arr,length);
    printf("INSERT SORT : ");
	printArr(arr,length);
    return 0;
}
    

