#include"header.h"
void Decoding(SSTable ST,char a[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	int q = 0;
	char code1[11];
	char code2;
	char b[1000] = {'\0'};
	char m[2] = {'\0'};
	FILE * decode;

    int t;
	for(t = 0; t <1000 ; t++)
	b[t] = '\0';
    //printf("%s",b);

	for(k=0; k<11 ; k++ )
	{
	code1[k] = '\0';
	}//code1[11]��Ԫ��ȫ����ֵΪ'\0'

	decode = fopen("d:\\TargetDoc.txt","w+");
	if( decode == NULL )
	{
		printf("�޷���TargetDoc.txt\n");
		exit(0);
	}//����TragetDoc.txt�ļ�


	else

		for(i=0; a[i] != '\0' ; i++)
		{
	       code2 = a[i];//��Encode��ȡһ��code
	       //printf("%c",code2);
           code1[j] = code2;   //��code2����code1����
           j++;

           strcpy(ST.elem[0].code,code1);//�ڱ�

        for (q = ST.length;  strcmp(code1,ST.elem[q].code)!=0 ;  q--);  //�Ӻ���ǰ��code1
		  {
		      //printf("6");
		      if(q)
		      {
			     m[0] = ST.elem[q].key;
			     //printf("%c",m[0]);
			     strcat(b,m);
			     m[0] = '\0';
			     m[1] = '\0';
			    // printf("%s",strcat(b,m));
			    //printf("%s",ST.elem[q].key);
                 for(k=0; k<11 ; k++ )
				 {
     	           code1[k] = '\0';
                 }//�ٴν�code1[8]��Ԫ��ȫ����ֵΪ\0
			       code2 = '\0';
                   j = 0;
		      }
		  }
		}
    int flag = 0;
    for(flag = 0; b[flag] != '\0'; flag++)
    {

        printf("%c",b[flag]);
        fprintf(decode,"%c",b[flag]);
    }
	fclose(decode);

}
