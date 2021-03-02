#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char String;
#define MAXSIZE 20

void Getnext(int *next,String *t)
{
    int i = 0;  //后缀
    int k = -1;  //前缀
    int len = strlen(t);
    next[0] = -1;
    
    while(i<len-1)
    {
        if ((k == -1) || (t[i] == t[k]))
        {
            k++;
            i++;
            if (t[i] == t[k])
            {
                next[i] = next[k];
            }
            else
            {
                *(next+i) = k;
            }
        }
        else
        {
            k = next[k];  //回溯
        }
    }    

}
int KMP(String *s,String *t)
{
    int next[MAXSIZE] = {0};
    Getnext(next, t);
    int i = 0;
    int j = 0;
    int lens = strlen(s);
    int lent = strlen(t);
    while (i < lens && j < lent)
    {
        if (j == -1 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; //回溯到最大子串的位置，返回值可能是-1
        }
    }
    if(j>=lent)
    {
        return i - lent;
    }
    else
    {
        return -1;
    }

}


int main()
{
    String s[] = "abacdababc";
    String t[] = "abab";
    int pos = KMP(s, t);
    printf("%d\n", pos);
    return 0;
}