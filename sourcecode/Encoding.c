#include"header.h"

int Encoding(SSTable ST,char a[])  //���ļ����б������
{
    int i = 0;
    int m = 0;
    int k = 0;
    char key;

    FILE * source;

    source = fopen("d:\\source.txt","r+");
    if(source == NULL)
    {
        printf("cannot open source.txt\n");
        exit(0);
    }//��Դ�ĵ�Source.txt

    else

        while( !feof(source) )
        {
            key = fgetc(source);         //��Source��ȡһ���ַ�key
            ST.elem[0].key = key;        //�ڱ�
            //printf("%c",ST.elem[0].key);
            for (i = ST.length;  ST.elem[i].key != key ; i--); //�Ӻ���ǰ��key
            {
                if(i)
                     {
                        for(k=0; ST.elem[i].code[k] !='\0' ; k++)////
                        a[m+k] = ST.elem[i].code[k];//���ҵ���code����a[]����////
                        m = m + k ;
                     }

           }
        }

       // printf();                       //�õ��������µ�code����

    fclose(source);
    return 0;

}



