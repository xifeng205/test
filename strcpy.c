#include<stdio.h>
#include<assert.h>

char *strcpy(char *dst,const char *src)
{
    assert((dst!=NULL)&&(src!=NULL));
    char *tmp=dst;
    while((*tmp++=*src++)!='\0');
    return dst;
}

void main()
{
    char test[10];
    strcpy(test,"12344");
    printf(test);
}
