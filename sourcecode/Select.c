#include"header.h"

void Select(Huffmantree HT,int n)    //在叶子结点中找parent为0且权值最小的两个结点，序号为s1,s2
{
    int i,j;

    for(i = 1; i<=n; i++)
    {
        if(HT[i].parent==0)
        {
            s1 = i;
            break;
        }
    }
    for(j = i+1; j<=n; j++)
    {
        if(HT[j].parent==0)
        {
            s2 = j;
            break;
        }
    }
    for(i = 1; i<=n; i++)
    {
        if(HT[i].parent==0)
        {
            if(HT[s1].weight>HT[i].weight)
            {
                if(s2!=i)
                {
                    s1 = i;
                }
            }
        }
    }
    for(j = 1; j<=n; j++)
    {
        if(HT[j].parent==0)
        {
            if(HT[s2].weight>HT[j].weight)
            {
                if(s1!=j)
                {
                    s2 = j;
                }
            }
        }
    }
    if(s1>s2)         //使s1为权值最小
    {
        int s3 = s1;
        s1 = s2;
        s2 = s3;
    }
}
