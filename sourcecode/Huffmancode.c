#include"header.h"
//w���Ȩֵ��������������HT�������������HC
void Huffmancoding(struct Text*head)
{
    int i,j,start,c,f,n,m;
    //n��Ҷ�ӽ�㣬m�����
    int w[100];
    char cd[100];
    struct Text*HOLD;
    FILE *fo;
    HOLD=head;
    for(n = 0; head&&head->a!=10000; n++)
    {
        w[n] = head->a;
        head = head->next;
    }
    head=HOLD;
    m = 2*n-1;
    HT = (Huffmantree)malloc((m+1)*sizeof(HTNode));       //0�ŵ�Ԫδ��
    for(i = 1; i<=n; i++)                        //��ʼ��
    {
        HT[i].weight = w[i-1];
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(i = n+1; i<=m; i++)                      //������������
    {
        HT[i].weight = 0;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(i = n+1; i<=m; i++)
    {
        Select(HT,i-1);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight+HT[s2].weight;
    }

    //��Ҷ�ӵ���������ÿ��Ҷ�ӽ��Ĺ���������
    HC = (Huffmancode)malloc((n+1)*sizeof(char*));         //����n��Ҷ�ӽ������ͷָ������
    cd[n-1] = '\0';                                         //���������
    for(i = 1; i<=n; i++)                         //��������������
    {
        start = n-1;                                   //���������λ��
        for(c = i,f = HT[i].parent; f!=0; c = f,f = HT[f].parent)            //��Ҷ�ӵ������������
        {
            if(HT[f].lchild==c)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
        }
        HC[i] = (char *)malloc((n-start)*sizeof(char));                   //Ϊ��i�����������ռ�
        strcpy(HC[i],&cd[start]);                              //��cd���Ʊ��뵽HC
    }

    fo = fopen("D:\\Statistic.txt", "w");

    fprintf(fo,"�ַ�\t\t���ִ���\tƵ��\t\t�������뱾");
    fprintf(fo,"\n");
    printf("Would you like to see the statistics on the screen?  (Y or N?)\n");
  if(getchar() == 'Y')
   {
        printf("The frequentness and codes of all characters are as follows:\n");

        printf("�ַ�\t\t���ִ���\tƵ��\t\t�������뱾\n");



        i=1;
        j = 1;
        while(head&&head->a!=10000)
        {
            if(head->word<0)
            {
                fprintf(fo,"%c\t\t\t%d\t\t%f%%", head->word, head->a,head->percentage);

                fprintf(fo,"\t");
                fputs(HC[i++],fo);


                fprintf(fo,"\n");
                printf("%c\t\t%d\t%f%%\t", head->word, head->a,head->percentage);
               puts(HC[j++]);
                printf("\n");
                head=head->next;
            }
            else
            {
                fprintf(fo,"%c\t\t%d\t\t%f%%", head->word, head->a,head->percentage);
                printf("%c\t%d\t%f%%\t", head->word, head->a,head->percentage);
               puts(HC[j++]);
        printf("\n");
                fprintf(fo,"\t");
                fputs(HC[i++],fo);
                fprintf(fo,"\n");
                head=head->next;
            }
       }
    }
    fclose(fo);
}

