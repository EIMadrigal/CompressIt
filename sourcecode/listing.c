#include"header.h"

int fun(SSTable ST)
{

	int i = 0;
	int k = 0;
	int n = 71;
	int h = 0;
	int jet = 0;
	char buf[1024];
	FILE *fp;


	fp = fopen("d:\\Statistic.txt", "r");
	if (fp == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}//打开Statistic.txt文件

	fgets(buf, 1024, fp);//跳过第一行

	//fseek(fp, 1024, SEEK_SET);

	for (i = 1; i< n; i++)
	{

		fgets(buf, 1024, fp);
		ST.elem[i].key = buf[0];
	    if(i == 49)
		{
		    fgets(buf, 1024, fp);
		}

		h = 0;
		if ((i > 50)&&(i < 70))
			k = 17;
        else if (i == 70)
            k = 19;
        else if (i == 49)
            k = 15;
		else k = 16;
        if( buf[0] < 0 )
            k = 17;
		for(k; buf[k] == '0'||buf[k]=='1'; k++)
		{
			ST.elem[i].code[h] = buf[k];//取哈夫曼码存入code内
			h++;
		}
		for(h; h < 11; h++)
		{
			ST.elem[i].code[h] = '\0';
		}
         //if( buf[0] < 0)
            //ST.elem[i].code[10] = '6';

	}


	for (jet = 1; jet < n; jet++)
	{
		int t;
		printf("%d %c ",jet,ST.elem[jet].key);
        for (t = 0; t < 11; t++)
        printf("%c",ST.elem[jet].code[t]);
		printf("\n");
	}

while(fclose(fp))
{
 fclose(fp);
}
	return 0;
}



