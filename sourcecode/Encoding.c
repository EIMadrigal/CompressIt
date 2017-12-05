#include"header.h"

int Encoding(SSTable ST,char a[])  //对文件进行编码输出
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
    }//打开源文档Source.txt

    else

        while( !feof(source) )
        {
            key = fgetc(source);         //从Source中取一个字符key
            ST.elem[0].key = key;        //哨兵
            //printf("%c",ST.elem[0].key);
            for (i = ST.length;  ST.elem[i].key != key ; i--); //从后往前找key
            {
                if(i)
                     {
                        for(k=0; ST.elem[i].code[k] !='\0' ; k++)////
                        a[m+k] = ST.elem[i].code[k];//将找到的code并入a[]后面////
                        m = m + k ;
                     }

           }
        }

    fclose(source);
    return 0;

}
