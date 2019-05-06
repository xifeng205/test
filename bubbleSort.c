#include<stdio.h>
#include<stdbool.h>

#define N 100

int bubble_sort(int src[],int len,int option)
{
    int j,i,t;
    /*降序排序  */
    if(option==0)
    {
        for( i=0;i<len-1;i++) 
            for(j=i;j<j-i-1;j++)
            {
                if(src[j] < src[j+1])
                    t=src[j],src[j]=src[j+1],src[j+1]=t;
            }

        return 0;
    }
    /*升序排序  */
    else if(option==1)
    {
        for( i=0;i<len-1;i++) 
            for(j=i;j<j-i-1;j++)
            {
                if(src[j] > src[j+1])
                    t=src[j],src[j]=src[j+1],src[j+1]=t;
            }

        return 0;
    }

    return -1;
}
bool quit=true;

void main()
{
    int ret;
    int i;
    int arry[N]={1,2,3,4,5,6,7,8,9};
    while(quit)
    {
        ret=bubble_sort(arry,10,1);
        if (ret==-1)printf("select sort type:\n");
        else
            for(i=0;i<10;i++)
                printf("the search is %d:\n",arry[i]);
        printf("press 'e' to end ,other to contiue.\n");
        if(getchar()=='e')quit=false;
    }

}
