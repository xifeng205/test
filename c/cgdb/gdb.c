#include <stdio.h>

int add(int x,int y)

{

    return x+y;

}

int main(int argc, char **arv)

{

    printf("%d", argc);
    int x = 10;

    int y = 20;

    int num = add(x,y);

    printf(" num = %d\n",num);
    printf(" num = %d\n",num);
    printf(" num = %d\n",num);

    return 0;

}
