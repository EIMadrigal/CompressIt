#include"header.h"

struct Text *command(struct txt *headate)
{
	struct Text*head;
	struct Text*p;
	struct Text*p1;
	struct Text*p2;
	struct Text*p3;
	struct Text*p4;
	struct Text*cycle1;
	struct Text*cycle2;
    struct Text*HOLD;
	struct txt*pre;
	struct txt *quanju;
    struct txt *q;
    struct txt*mid;

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
		n = 0;                   //��ʼΪ0
		do                      //ȷ����һ��headate��λ��(��һ����ǰ��ڵ��ַ���ͬ��λ��)
		{
			if (zifu != q->date)
			{
				headate = q;
				break;
			}
			q = q->next;
		}
		while (q != NULL);
		q = quanju;            //��q�������ص�����Ŀ�ʼ
		if (headate == q)
		{
			headate = NULL;
		}//�ü�����䣬���ǵ�����������headate��Ϊ��
		do
		{
			if (zifu == q->date)//ɾ�������������һ���ڵ��ַ���ͬ�Ľڵ㲢����
			{//ɾ����ǰ�ڵ��pre��¼��һ�����,��������
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

		if (p == head)//�����һ���ڵ��ֵ
		{
			p1->word = zifu;
			p1->a = n;
			p = NULL;//ʹ��һ��ѭ������else���
			p2 = (struct Text*)malloc(LEN);//����һ��λ���������Ľ�㣬���ڲ���
			p1->next = p2;
			p2->a = 10000;
			p2->next = NULL;
		}
		else
		{
			cycle1 = head;
			if (n <= cycle1->a)//�½����Ľ����Ҫ�嵽������ǰ������
			{
				p3 = (struct Text*)malloc(LEN);
				p3->a = n;
				p3->word = zifu;
				p3->next = head;
				head = p3;
			}
			if (n > cycle1->a)//�½����Ľ����Ҫ�嵽�����м�����
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

	while(head&&head->a!=10000)
	{
		sum = sum+head->a;
		head=head->next;
	}
	head = HOLD;
	while(head&&head->a!=10000)
	{
		head->percentage = (float)(head->a)/(float)(sum)*100;
		head=head->next;
	}

	head = HOLD;
	return(head);

}
