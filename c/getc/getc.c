/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-31 15:29
 * Last modified : 2020-03-31 15:29
 * Filename      : getc.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    
    char filename[20];

    printf("please enter file name from term:\n");
    scanf("%s", filename);

    if ((fp = fopen(filename, "w+")) == NULL)
    {
        fprintf(stderr, "cant open the file %s\n", filename);
        exit(0);
    }
    printf("please enter char to filename%s\n", filename);
    char c = getchar();

    while (c != '3')
    {
       c = getchar();
       fputc(c, fp);
    }

    while (c != EOF)
    {
        c = fgetc(fp);
        printf("%c\n", c);
    }
}
