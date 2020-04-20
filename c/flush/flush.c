/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-17 13:43
 * Last modified : 2020-03-17 13:43
 * Filename      : flush.c
 * Description   : 
*********************************************************************/
/* #include <stdio.h> */
/*  */
/* int main(int argc, char **argv) */
/* { */
/*  */
/*     FILE *fp; */
/*  */
/*     char buf[50] = {0}; */
/*  */
/*     if((fp = fopen("flush.txt", "rw")) == NULL){ */
/*         fprintf(stderr, "file can not open!!\n"); */
/*     } */
/*     else{ */
/*         printf("---------------\n"); */
/*         fputs("tesfdfdfdfsdft", fp); */
/*         #<{(| fflush(fp); |)}># */
/*         #<{(| fflush(fp); |)}># */
/*         fgets(buf, 20, fp); */
/*         puts(buf); */
/*         fclose(fp); */
/*     } */
/*  */
/*     return 1; */
/* } */
/* fflush example */
#include <stdio.h>
char mybuffer[80];
int main()
{
    FILE * pFile;
    pFile = fopen ("flush.txt","r+");
    if (pFile == NULL) perror ("Error opening file");
    else {
        fputs ("test",pFile);
        fflush (pFile);    // flushing or repositioning required
        sync()
        fgets (mybuffer,80,pFile);
        puts (mybuffer);
        fclose (pFile);
        return 0;
    }
}
