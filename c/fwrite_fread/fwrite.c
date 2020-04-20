/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-31 21:13
 * Last modified : 2020-03-31 21:13
 * Filename      : fwrite.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
#define SIZE 10
    char *filename = "file.dat";

    typedef struct {
        char name[10];
        int age;
        int class;
        char addr[15];
    }student;

    student stu[10] = {
        {"xiaoming", 18, 1, "wangpu"},
        {"zhangsan", 19, 1, "cuicha"},
        {"lisi", 20, 3, "renghe"}};

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "cant find file:%s\n", filename);
        exit(0);
    };
    int fd = fileno(fp);
    printf("%d\n", fd);

    for (int i = 0;i < SIZE; i++) {
        int ret = fwrite(&stu[i], sizeof(student), 1, fp);
        if (ret != 1) {
            fprintf(stderr, "%s:wrire error!\n", filename);
            exit(0);
        }
    }
    fclose(fp);
    return 0;
}
