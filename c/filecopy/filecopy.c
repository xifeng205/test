/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-31 17:08
 * Last modified : 2020-03-31 17:08
 * Filename      : filecopy.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <stdlin.h>

int main(int argc, char **argv)
{
    FILE *in, *out;
    /* char filein[20], fileout[20]; */
    /* printf("please enter input file:\n"); */
    if ((in = fopen("file1", "r")) == NULL)
    {
        fprintf(stderr, "cant open the file:\n", "file1");
    }

}
