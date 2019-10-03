#include<stdio.h>
#include<stdbool.h>
int factor(int n)
{
    if(n==0 || n==1)return 1;
    int sum=n*factor(n-1);
} 
bool quit=true;
void main(){
    int n;

    while(quit)
    {
        printf("intput a intger:");
        scanf("%d",&n);
        int sum= factor(n);
        printf("the result is: %d\n",sum);
        printf("press e  to end ,any key to continue \n");
        if(getchar()=='e')quit=false;
    }
}

