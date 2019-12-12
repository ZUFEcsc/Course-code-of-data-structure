#include <stdio.h>
#include <stdlib.h>
 
#define TRUE     1
#define FALSE    0
 
typedef struct BiNode
{
    int data;
    struct BiNode *lchild, *rchild;
}BiNode, *BiTree;
 
int SearchBST (BiTree T, int key, BiTree f, BiTree *p)
{
    if(!T)
    {
        *p = f;
        return FALSE;
    }
    else if(T->data == key)
    {
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
    {
        SearchBST(T->lchild, key, T, p);      //递归寻找，根据二叉排序树的性质
    }
    else
    {
        SearchBST(T->rchild, key, T, p);
    }
}
 
void InsertBST (int key, BiTree *T)
{
    BiTree p, s;
    if(!SearchBST(*T, key, NULL, &s))                  //查找二叉排序树中是否已经存在key值
    {
        p = (BiTree)malloc(sizeof(BiNode));
        p->data = key;
        p->lchild = p->rchild = NULL;
        if(!s)                                         //若二叉排序树为空，则插入根节点
        {
            *T = p;
        }
        else if(key < s->data)
        {
            s->lchild = p;
        }
        else
        {
            s->rchild = p;
        }
    }
}
 
void CreatBST (BiTree *T, int *arry)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        InsertBST(arry[i], T);
    }
}
 
void PreOrderTree (BiTree T)
{
    if(!T)
    {
        return;
    }
    printf("%d ", T->data);
    PreOrderTree(T->lchild);
    PreOrderTree(T->rchild);
}
 
void Delete (int key, BiTree *p)                      //删除查找的结点
{
    BiTree q, s;
    if(!(*p)->rchild)
    {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if(!(*p)->lchild)
    {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    {
        q = *p;
        s = q->lchild;
        while(s->rchild)
        {
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;
        if(q != *p)
        {
            q->rchild = s->lchild;
        }
        else
        {
            (*p)->lchild = s->lchild;
        }
        free(s);
    }
}
 
void DeletrBST (BiTree *T, int key)
{
    if(!*T)
    {
        return;
    }
    else if(key == (*T)->data)
    {
        Delete(key, T);
    }
    else if(key < (*T)->data)
    {
        DeletrBST(&((*T)->lchild), key);
    }
    else
    {
        DeletrBST(&((*T)->rchild), key);
    }
}
 
int main ()
{
    BiTree T = NULL;
    int arry[100], i, key, n;
    printf("Please enter the number of nodes :");
    scanf("%d",&n); 
    printf("Please enter the node number in turn :\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &(arry[i]));
    }
    CreatBST(&T, arry);
    
    printf("Preorder traversal results ：");
    PreOrderTree(T);
    printf("\nEnter delete num:\n");
    scanf("%d", &key);
    DeletrBST(&T, key);
    
    printf("Preorder traversal results ：");
    PreOrderTree(T);
    return 0;
}
//9
//9 5 10 0 6 11 -1 1 2
//10
