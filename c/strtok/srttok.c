/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-23 10:00
 * Last modified : 2020-03-23 10:00
 * Filename      : srttok.c
 * Description   : 
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char str[] = "ad fd,d:dfk:vj df jjdfk:dkf";
    char *delim = ":,";
    char *st = strtok(str, delim);
    

    while (st){
        printf("%s", st);
        st = strtok(NULL, delim);
    }
}
