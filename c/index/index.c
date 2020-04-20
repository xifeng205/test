/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-24 22:29
 * Last modified : 2020-03-24 22:29
 * Filename      : index.c
 * Description   : 
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    /* char *i = (char *)malloc(10*sizeof(char)); */
    /* char buf[10] = "134"; */

    /* *i = buf[0]; */
    /* printf("%s\n", i); */
    /* char var1 = 10; */
    /* #<{(| char var2[10] = "12345678"; |)}># */
    /* char var3 = 2; */
    /* char *p = &var1; */
    /* char **pp = &p; */
    /*  */
    /* printf("the address of size is %ld\n", sizeof &var3); */
    /* printf("the address of var1 is %p\n", &var1); */
    /* printf("the address of var2 is %p\n", &var2); */
    /* printf("the address of var3 is %p\n", &var3); */
    /* printf("the address of  p is %p\n", p); */
    /* printf("the address of  p is %d\n", *p); */
    /* printf("the address of  p is %p\n", pp); */
    /* printf("the address of  pp is %p\n", *pp); */
    /* printf("the data of  pp is %d\n", **pp); */

    typedef struct {
        int a;
        int b;
        char *c;
        char *d;
        float e;
        float *f;
    }aa;

    aa bb = {1, 2, "d", "d", .3, "g"};
    /* printf("%d\n", bb.a); */
    /* printf("%f\n", bb.e); */

    aa *cc = &bb;
    aa dd = *cc;

    printf("dd = %d\n", dd.a);
    /* cc->a j 3; */

    /* printf("cc = %d\n", cc->a); */

    *cc = dd;

    /* printf("bb = %d\n", bb.a); */
    printf("cc = %d\n", cc->a);
}


