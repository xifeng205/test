/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-31 11:25
 * Last modified : 2020-03-31 11:25
 * Filename      : strchr.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{
    char *str = "ho,dsf,c,d";
    /* char *head = strchr(str, 'd'); */
    /* printf("%s\n", str); */
    /* printf("%s\n", head); */

    /* char *s="012345678901234567890123456789"; */
    /* char *p; */
    /* p=strchr(s,'5'); */
    /* printf("%s\n",p); */

    char *next;

    /* while (next = strchr(str, ',')) */
    /* { */

    next = strchr(str, ',');
    printf("%s\n", next);
    next++;
    next= strchr(next, ',');
    printf("%s\n", next);
    next++;
    next = strchr(next, ',');
    printf("%s\n", next);
    /* } */
}
    /* } */
/* } */
    /* } */
/* } */
