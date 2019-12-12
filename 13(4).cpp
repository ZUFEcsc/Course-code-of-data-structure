#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct _blockIndex
{
    int key;
    int len;
    int *first;
}blockInfo,BlockIndex[MAXSIZE];

int Binary_Search(BlockIndex B, int key, int n,int *loc)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    while (low<=high)
    {
        mid = (high + low) / 2;
        if (B[mid].key == key)
            return mid;
        else if (B[mid].key < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (B[mid].key < key&&key < B[mid + 1].key)
        *loc = mid + 1;
    else
        *loc = mid;
    return -1;
}

int main()
{
	int aa[1010]={0}; 
	int num;
	printf("Please input the number of numbers to be found :");
	scanf("%d",&num);
	printf("Please input numbers in turn :");
	for(int i=0;i<num;i++)
	{
		scanf("%d",&aa[i]);
	} 
    BlockIndex BI;
    int n,loc,ret;
    BI[0].key = aa[num/3];
    BI[0].len = num/3+1;
    BI[0].first = aa;
    
	BI[1].key = aa[num/3+2];
    BI[1].len = num/3-1;
    BI[1].first = aa+(num/3+1);

    BI[2].key = aa[num/3*2+1];
    BI[2].len = num/3;
    BI[2].first = aa + (num/3*2);
    printf("input number to search :\n");
    scanf("%d", &n);
    ret = Binary_Search(BI, n, 3, &loc);
    if (ret != -1)
        loc = ret;
    for (int i = BI[loc].first - aa; i < BI[loc].first - aa + BI[loc].len; i++)
        if (aa[i] == n)
        {
            printf("find index : %d", i);
            break;
        }
    return 0;
}
//9
//18 5 27 13 57 36 96 62 77
//36
