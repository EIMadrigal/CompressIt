#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>


#define LEN sizeof(struct Text)

typedef struct HTNode
{
int weight;
int parent,lchild,rchild;
}HTNode,*Huffmantree;        //����������

typedef char * * Huffmancode;//��̬��������洢�����������
    Huffmantree HT;
    Huffmancode HC;
	int s1,s2;

struct txt
{
	char date;
	struct txt*next;
};//�ı�����

struct Text
{
	char word;
	int a;
	float percentage;
	struct Text*next;
};//������ͳ������


//typedef char KeyType;

typedef struct
{
	char key;
	char  code[11];
}ElemType;//�����ǲ��ұ�����Ԫ�����Ͷ���

typedef struct
{
    ElemType * elem;
    int      length;
}SSTable;//�����Ǿ�̬���ұ����Ͷ���



struct txt *read();//���뺯��
struct Text *command(struct txt *headate);//������
void Select(Huffmantree HT,int n);
void Huffmancoding(struct Text*head);
void Checking();
int fun(SSTable ST);
int Encoding(SSTable ST,char a[]);
void Decoding(SSTable ST,char a[]);
void codedecode(char a[],char *p);
void check();
