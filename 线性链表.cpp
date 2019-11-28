#include <stdio.h>
#define maxSize 7
typedef struct {
    int data;
    int cur;
}component;

void reserveArr(component *array);
int initArr(component *array);
void insertArr(component * array,int body,int add,int a);
void deletArr(component * array,int body,int a);
int selectElem(component * array,int body,int elem);
void amendElem(component * array,int body,int oldElem,int newElem);
void displayArr(component * array,int body);
int mallocArr(component * array);
void freeArr(component * array,int k);

int main() {
    component array[maxSize];
    int body=initArr(array);
    printf("Now list£º\n");
    displayArr(array, body);
	int insert_index,insert_num;
	printf("Input the index & number tou want to insert:");
	scanf("%d %d",&insert_index,&insert_num);
	printf("Insert %d to %d:",insert_num,insert_index);
    insertArr(array,body,insert_index,insert_num);
    displayArr(array,body);
    printf("Input the number you want to delete:");
	int delete_num;
	scanf("%d",&delete_num);
    deletArr(array, body, delete_num);
    displayArr(array, body);
    
    int select_num;
    printf("Input thie num you want to find the index:");
    scanf("%d",&select_num);
    printf("The index of this num is:");
    int selectAdd=selectElem(array,body,select_num);
    printf("%d\n",selectAdd);
    printf("Input the num you want to change:");
    int change_num;
    scanf("%d",&change_num);
    amendElem(array,body,select_num,change_num);
    displayArr(array, body);
    return 0;
}

void reserveArr(component *array){
    for (int i = 0;i < maxSize;i++) {
        array[i].cur=i+1;
    }
    array[maxSize-1].cur=0;
}

int initArr(component *array,int nn){
    reserveArr(array);
    int body = mallocArr(array);
    int tempBody = body;
    for (int i = 1;i < nn;i++) {
        int j=mallocArr(array);
        array[tempBody].cur=j;
        array[j].data=i-1;
        tempBody=j;
	}
    array[tempBody].cur=0;
    return body;
}

void insertArr(component * array,int body,int add,int a){
    int tempBody=body;
    for (int i = 1;i < add;i++) {
        tempBody=array[tempBody].cur;
    }
    int insert=mallocArr(array);
    array[insert].cur=array[tempBody].cur;
    array[insert].data=a;
    array[tempBody].cur=insert; 
}

void deletArr(component * array,int body,int a){
    int tempBody = body;
    while (array[tempBody].data != a) {
        tempBody = array[tempBody].cur;
        if (tempBody == 0) {
            printf("NOT FOUND!\n");
            return;
        }
    }
	int del=tempBody;
    tempBody=body;
	while (array[tempBody].cur!=del) {
        tempBody=array[tempBody].cur;
    }
	array[tempBody].cur=array[del].cur;
  
    freeArr(array, del);
}

int selectElem(component * array,int body,int elem){
    int tempBody=body;
    while (array[tempBody].cur!=0) {
        if (array[tempBody].data==elem) {
            return tempBody;
        }
        tempBody=array[tempBody].cur;
    }
    return -1;
}

void amendElem(component * array,int body,int oldElem,int newElem){
    int add=selectElem(array, body, oldElem);
    if (add==-1) {
        printf("WITHOUT THIS NUMBER!\n");
        return;
    }
    array[add].data=newElem;
}

void displayArr(component * array,int body){
    int tempBody=array[body].cur;
    while (array[tempBody].cur) {
//      printf("%d,%d  |",array[tempBody].data,array[tempBody].cur);
		printf("%d,",array[tempBody].data);
        tempBody=array[tempBody].cur;
    }
    printf("%d\n",array[tempBody].data);
//    printf("%d,%d\n",array[tempBody].data,array[tempBody].cur);
}

int mallocArr(component * array){
    int i=array[0].cur;
    if (array[0].cur) {
        array[0].cur=array[i].cur;
    }
    return i;
}

void freeArr(component * array,int k){
    array[k].cur=array[0].cur;
    array[0].cur=k;
}


