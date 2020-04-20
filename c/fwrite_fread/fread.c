
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

    student stu[10] = {0};
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "cant find file:%s\n", filename);
        exit(0);
    };
    int fd = fileno(fp);
    printf("%d\n", fd);

    for (int i = 0;i < SIZE; i++) {
        int ret = fread(&stu[i], sizeof(student), 1, fp);
        printf("%d\n", ret);
        printf("%s\n", stu[i].name);
        printf("%d\n", stu[i].age);
        if (ret != 1) {
            if (!feof(fp))
            fprintf(stderr, "%s:end file\n", filename);
            exit(0);
        }
    }
}
