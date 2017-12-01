#include "header.h"

void check()
{
    FILE *source;
    FILE *target;
    int i,j,k;
    unsigned char s,t;
    source = fopen("D:\\source.txt","r");
    target = fopen("D:\\TargetDoc.txt","r");
    j = k = 0;
    if(target == NULL)
    {
        printf("未接收到数据");
        exit(0);
    }

    for(i = 1;i < 100000;i++)
    {
        if(source == EOF&&target == EOF)
        {
            break;
        }
        s = fgetc(source);
        t = fgetc(target);
        if(s != t)
        {
            printf("第%d个数据传输错误",i);
            printf("\n");
            j = 1;
        }

    }
    if(j == k)
        {
            printf("数据传输成功");
        }
        fclose(source);
        fclose(target);
}

