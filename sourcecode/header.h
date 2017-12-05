#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#define LEN sizeof(struct Text)

typedef struct HTNode
{
	int weight;
	int parent,lchild,rchild;
}HTNode,*Huffmantree;        //定义结点类型

typedef char * * Huffmancode;//动态分配数组存储哈夫曼编码表
Huffmantree HT;
Huffmancode HC;
int s1,s2;

struct txt
{
	char date;
	struct txt*next;
};//文本链表

struct Text
{
	char word;
	int a;
	float percentage;
	struct Text*next;
};//排序后的统计链表

typedef struct
{
	char key;
	char  code[11];
}ElemType;//以上是查找表数据元素类型定义

typedef struct
{
    ElemType * elem;
    int      length;
}SSTable;//以上是静态查找表类型定义

struct txt *read();//输入函数
struct Text *command(struct txt *headate);//排序函数
void Select(Huffmantree HT,int n);
void Huffmancoding(struct Text*head);
void Checking();
int fun(SSTable ST);
int Encoding(SSTable ST,char a[]);
void Decoding(SSTable ST,char a[]);
void codedecode(char a[],char *p);
void check();
