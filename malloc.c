#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

char cpy(char *dst,const char *src)
{
    assert((dst!=NULL)&&(src!=NULL));
    strcpy(dst,"12344");
}


void main()
{

    char  *dest=(char *)malloc(100);
    /* char *test=dest; */
    cpy(dest,1);
    printf(dest);
}
