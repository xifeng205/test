#include<stdio.h>

#define XMK_STR(x,y)  x##y

int main(int argc,char **argv)
{
    printf("%s",XMK_STR(5,a));

}

