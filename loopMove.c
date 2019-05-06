#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<string.h>

bool loop_move( char *src,int n)
{
    char tmp[100];
    assert(src!=NULL);
    int len=strlen(src)-n;
    memcpy(tmp,src+len,n);
    memcpy(src+len,src,len);
    memcpy(src,tmp,n);
    return true ;
}

void main()
{
     char test[5]="12345";
    loop_move(test,3);
    printf("%s\n",test);
}
