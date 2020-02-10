#include "header.h"

//w存放权值，构建哈夫曼树HT，求哈夫曼编码HC
void Huffmancoding(struct Text* head)
{
	int i, j, start, c, f, n, m;
	//n个叶子结点，m个结点
	int w[100];
	char cd[100];
	struct Text* HOLD;
	FILE* fo;
	HOLD = head;
	for (n = 0; head && head->a != 10000; n++)
	{
		w[n] = head->a;
		head = head->next;
	}
	head = HOLD;
	m = 2 * n - 1;
	HT = (Huffmantree)malloc((m + 1) * sizeof(HTNode));   //0号单元未用
	for (i = 1; i <= n; i++)           //初始化
	{
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)      //构建哈夫曼树
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//从叶子到根逆向求每个叶子结点的哈夫曼编码
	HC = (Huffmancode)malloc((n + 1) * sizeof(char*));  //分配n个叶子结点编码的头指针向量
	cd[n - 1] = '\0';    //编码结束符
	for (i = 1; i <= n; i++)        //逐个求哈夫曼编码
	{
		start = n - 1;        //编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)    //从叶子到跟逆向求编码
		{
			if (HT[f].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));    //为第i个结点编码分配空间
		strcpy(HC[i], &cd[start]);        //从cd复制编码到HC
	}

	fo = fopen("D:\\Statistic.txt", "w");

	fprintf(fo, "字符\t\t出现次数\t频度\t\t哈夫曼码本");
	fprintf(fo, "\n");
	printf("Would you like to see the statistics on the screen?  (Y or N?)\n");
	if (getchar() == 'Y')
	{
		printf("The frequentness and codes of all characters are as follows:\n");

		printf("字符\t\t出现次数\t频度\t\t哈夫曼码本\n");

		i = 1;
		j = 1;
		while (head && head->a != 10000)
		{
			if (head->word < 0)
			{
				fprintf(fo, "%c\t\t\t%d\t\t%f%%", head->word, head->a, head->percentage);

				fprintf(fo, "\t");
				fputs(HC[i++], fo);

				fprintf(fo, "\n");
				printf("%c\t\t%d\t%f%%\t", head->word, head->a, head->percentage);
				puts(HC[j++]);
				printf("\n");
				head = head->next;
			}
			else
			{
				fprintf(fo, "%c\t\t%d\t\t%f%%", head->word, head->a, head->percentage);
				printf("%c\t%d\t%f%%\t", head->word, head->a, head->percentage);
				puts(HC[j++]);
				printf("\n");
				fprintf(fo, "\t");
				fputs(HC[i++], fo);
				fprintf(fo, "\n");
				head = head->next;
			}
		}
	}
	fclose(fo);
}
