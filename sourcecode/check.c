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
        printf("δ���յ�����");
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
            printf("��%d�����ݴ������",i);
            printf("\n");
            j = 1;
        }

    }
    if(j == k)
        {
            printf("���ݴ���ɹ�");
        }
        fclose(source);
        fclose(target);
}

