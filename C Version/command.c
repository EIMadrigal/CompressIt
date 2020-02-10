#include "header.h"

struct Text* command(struct txt* headate)
{
	struct Text* head;
	struct Text* p;
	struct Text* p1;
	struct Text* p2;
	struct Text* p3;
	struct Text* p4;
	struct Text* cycle1;
	struct Text* cycle2;
	struct Text* HOLD;
	struct txt* pre;
	struct txt* quanju;
	struct txt* q;
	struct txt* mid;

	char zifu;
	int n;
	int sum = 0;

	p1 = p2 = head = (struct Text*)malloc(LEN);
	head->a = 0;
	p = head;
	pre = NULL;
	for (n = 0; headate != NULL;)
	{
		zifu = headate->date;
		pre = quanju = q = headate;
		n = 0;    //初始为0
		do        //确定下一个headate的位置(下一个与前面节点字符不同的位置)
		{
			if (zifu != q->date)
			{
				headate = q;
				break;
			}
			q = q->next;
		} while (q != NULL);
		q = quanju;            //将q重新拉回到链表的开始
		if (headate == q)
		{
			headate = NULL;
		}//得加上这句，考虑到最后情况，将headate赋为空
		do
		{
			if (zifu == q->date)//删除所有与链表第一个节点字符相同的节点并计数
			{//删除当前节点后，pre记录上一个结点,连接链表
				n = n + 1;
				mid = q;
				q = mid->next;
				if (mid != quanju)
					pre->next = q;
				free(mid);
			}
			else
			{
				pre = q;
				q = q->next;
			}
		} while (q != NULL);

		if (p == head)//输入第一个节点的值
		{
			p1->word = zifu;
			p1->a = n;
			p = NULL;//使下一次循环进入else语句
			p2 = (struct Text*)malloc(LEN);//建立一个位于链表最后的结点，便于插入
			p1->next = p2;
			p2->a = 10000;
			p2->next = NULL;
		}
		else
		{
			cycle1 = head;
			if (n <= cycle1->a)//新建立的结点需要插到链表最前面的情况
			{
				p3 = (struct Text*)malloc(LEN);
				p3->a = n;
				p3->word = zifu;
				p3->next = head;
				head = p3;
			}
			if (n > cycle1->a)//新建立的结点需要插到链表中间的情况
			{
				do
				{
					cycle2 = cycle1;
					cycle1 = cycle1->next;
				} while (n >= cycle1->a);

				p4 = (struct Text*)malloc(LEN);
				p4->a = n;
				p4->word = zifu;
				cycle2->next = p4;
				p4->next = cycle1;
			}
		}
	}
	HOLD = head;
	printf("\n");

	while (head && head->a != 10000)
	{
		sum = sum + head->a;
		head = head->next;
	}
	head = HOLD;
	while (head && head->a != 10000)
	{
		head->percentage = (float)(head->a) / (float)(sum) * 100;
		head = head->next;
	}

	head = HOLD;
	return(head);
}
