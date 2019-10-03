#include<stdio.h>
#include<stdbool.h>

#define N 100

int bsearch(int src[],int search,int low,int high)
{
    int mid;
    while(low<high-1)
    {
        mid=(low+high-1)/2;
        if(src[mid]==search)return search;
        else if(src[mid]<search)low=mid;
        else if(src[mid]>search)high=mid;
    }
    return -1;
}
bool quit=true;

void main()
{
    int ret;
    int key;
    int arry[N]={'1',2,3,4,5,6,7,8,};
    while(quit)
    {
        printf("input the search value\n");
        scanf("%d",&key);
        ret=bsearch(arry,key,0,8);
        if (ret==-1)printf("no find\n");
        else printf("the search is %d:\n",ret);
        printf("press 'e' to end ,other to contiue.\n");
        if(getchar()=='e')quit=false;
    }

}
