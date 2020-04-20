#include <stdio.h>

int main(int argc, char **argv)
{
    char buf[4][2] = {"2","3","8"};
    int i;
    char *p = buf;
    for (i = 0; i<10; i++)
    {
        int a = atoi(p);
        p++;
        printf("%d\n", a);
    }
}
