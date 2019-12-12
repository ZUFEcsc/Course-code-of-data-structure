#include<stdio.h>
#include<stdlib.h>
 #include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
}BTNode;
 
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b) ? a : b;
}
 
BTNode* newNode(int key)
{
    struct Node* node = (BTNode*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}
 
BTNode* ll_rotate(BTNode* y)
{
    BTNode *x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
 
BTNode* rr_rotate(BTNode* y)
{
    BTNode *x = y->right;
    y->right = x->left;
    x->left = y;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
 
int getBalance(BTNode* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
BTNode* insert(BTNode* node, int key)
{
 
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key) //LL型
        return ll_rotate(node);
    if (balance < -1 && key > node->right->key)     //RR型
        return rr_rotate(node);
    if (balance > 1 && key > node->left->key)     //LR型
    {
        node->left = rr_rotate(node->left);
        return ll_rotate(node);
    }
    if (balance < -1 && key < node->right->key)     //RL型
    {
        node->right = ll_rotate(node->right);
        return rr_rotate(node);
    }
    return node;
}
 
 
void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int xx[100]={0};
 
int main()
{
    BTNode *root = NULL;
	int ax[100]={0};
	//	9 5 10 0 6 11 -1 1 2 
	int n;
	printf("Please enter the number of nodes :");
    scanf("%d",&n); 
    printf("Please enter the node number in turn :\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &(ax[i]));
        root = insert(root,ax[i]);
    }
 
    printf("Preorder traversal results ：");
//    9 1 0 -1 5 2 6 10 11
    preOrder(root);
    return 0;
}
