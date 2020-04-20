/**********************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-01-26 23:50
 * Last modified : 2020-01-26 23:50
 * Filename      : fgets.c
 * Description   : 
**********************************************************/
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv)
{
    FILE *fp;
    if ((fp = fopen("fopen", "r")) == NULL) {
        fprintf(stderr, "cant open the file:%s\n", "fopen");
        exit(0);
    }
    if (feof(fp)) return 0;
    size_t size = 512;
    char *line = malloc(size * sizeof(char));

    if (!fgets(line, size, fp)) {
        free(line);
        return 0;
    }
    printf("%s\n", line);
    int fd = fileno(fp);
    printf("%d\n",fd);
    fclose(fp);
}
