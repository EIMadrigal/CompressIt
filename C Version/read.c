#include "header.h"

struct txt* read()           //建立文本链表函数
{
	int n;
	struct txt* p1;
	struct txt* p2;
	struct txt* head;
	struct txt* temp;

	FILE* fp;
	fp = fopen("D:\\source.txt", "r");

	if (fp == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}

	else
	{
		n = 0;
		p1 = p2 = (struct txt*)malloc(sizeof(struct txt));
		p1->date = fgetc(fp);
		head = NULL;
		while (p1->date != EOF)
		{
			n++;
			if (n == 1)
				head = p1;
			else
				p2->next = p1;

			p2 = p1;
			p1 = (struct txt*)malloc(sizeof(struct txt));
			p1->date = fgetc(fp);
		}
		p2->next = NULL;    //这句得加上，否则尾结点的next指针就悬空了
		temp = head;
		printf("The passage is as follows:\n");
		while (temp)
		{
			printf("%c", temp->date);
			temp = temp->next;
		}
		fclose(fp);
		return (head);
	}
}
