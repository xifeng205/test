#include<stdio.h>
#include<assert.h>

char *strlen(const char *src)
{
    int len=0;
    assert(src!=NULL);
    while((*src++)!='\0')len++;
    return len;
}

void main()
{
    int len;
    const  char *test="12344";
    len= strlen(test);
    printf("the len is %d\n",len);
}
