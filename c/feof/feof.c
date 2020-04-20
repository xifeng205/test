/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-23 14:03
 * Last modified : 2020-03-23 14:03
 * Filename      : feof.c
 * Description   : 
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp = fopen("feof.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "the file of feof.txt can not open\n" );
        exit(-1);
    }
    if (!feof(fp)) {
        printf("file empty");
        exit(-1);
    }
    return 0;
}
