#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#define MAX_L 3
typedef struct Arr 
{
    int *pBase;  //存储的是第一个元素的地址
    int len;  //数组所能容纳的最大元素的地址
    int cnt;  //当前数组有效元素的地址
}Arr;

//函数的声明
void Init_arr(Arr *pArr,int length);    //初始化
void Show_arr(Arr *pArr);               //打印
bool Append_arr(Arr *pArr, int val);    //追加
bool Is_empty(Arr *pArr);               //判断是否为空
bool Is_full(Arr *pArr);                //判断是否满了，达到最大的容纳大小 
bool Insert_arr(Arr *pArr,int pos,int val); //指定位置插入，pos的值从1开始，pos<=元素个数+1,含有追加的功能
bool Delete_arr(Arr *pArr, int pos, int *pval); //val删除的值，pos的值从1开始，pos<=元素个数
void Inversion_arr(Arr *pArr);      //倒置
void Sort_arr(Arr *pArr);           //排序


//主函数
int main()
{
    int val = 0;
    Arr arr;
    Init_arr(&arr,5);//初始化
    Show_arr(&arr);
    Append_arr(&arr, 1);
    Append_arr(&arr, -10);
    Append_arr(&arr, 4);
    Append_arr(&arr, 54);
    Append_arr(&arr, 62);
    Append_arr(&arr, 16);
    //Insert_arr(&arr, 6, 12);

    // if(Delete_arr(&arr, 5, &val))
    // {
    //     printf("删除的元素是%d\n", val);
    // }
    Inversion_arr(&arr);
    Show_arr(&arr);
    Sort_arr(&arr);
    Show_arr(&arr);

    return 0;
}


void Init_arr(Arr *pArr,int length)
{
    pArr->pBase = (int *)malloc(sizeof(int) * length); //开辟动态空间
    if(NULL == pArr->pBase)
    {
        printf("%s\n", strerror(errno));
        exit(-1); //终止整个程序
    }
    else
    {
        pArr->len = length;
        pArr->cnt = 0;
    }
    return;
}


bool Is_empty(Arr *pArr)
{
    if(0 == pArr->cnt)
    {
        return true;  //为空
    }
    else
    {
        return false; //非空
    }
}


void Show_arr(Arr *pArr)
{
    if(Is_empty(pArr))  //空返回false
    {
        printf("数组为空\n");
    }
    else
    {
        int i = 0;
        for (i = 0; i < pArr->cnt; i++)
        {
            printf("%d ", pArr->pBase[i]);  //等价于 *(pArr->pBase+i)
        }
        printf("\n");
    }
}


bool Is_full(Arr *pArr)
{
    if(pArr->cnt == pArr->len)
    {
        return true;  //满了
    }
    else
    {
        return false;  //没满
    }
}


bool Append_arr(Arr *pArr,int val)
{
    //满是返回true
    if(Is_full(pArr))
    {
        //怎加容量，一次增加MAX_L
        int *pa = (int *)(realloc(pArr->pBase, sizeof(int) * (MAX_L + pArr->len)));
        if(pa==NULL)
        {
            perror("增容");   //增容失败
            return false;
        }
        printf("增容成功呢！\n");
        pArr->len += 3;
        pArr->pBase = pa;
    }

    pArr->pBase[pArr->cnt] = val;
    ++(pArr->cnt);
    return true;
}


bool Insert_arr(Arr *pArr,int pos,int val)
{
    int i = 0;
    if( Is_full(pArr) )  //满了
    {
        //怎加容量，一次增加MAX_L
        int *pa = (int *)(realloc(pArr->pBase, sizeof(int) * (MAX_L + pArr->len)));
        if(pa==NULL)
        {
            perror("增容");   //增容失败
            return false;
        }
        printf("增容成功呢！\n");
        pArr->len += 3;
        pArr->pBase = pa;
    }
    if (pos < 1 || pos > pArr->cnt + 1)
    {
        return false;
    }
    for (i = pArr->cnt - 1; i >= pos - 1; i--)
    {
        pArr->pBase[i + 1] = pArr->pBase[i];
    }
    pArr->pBase[pos-1] = val;
    (pArr->cnt)++;
    return true;
}


bool Delete_arr(Arr *pArr, int pos, int *pval)
{
    int i = 0;
    if(Is_empty(pArr))
    {
        return false;
    }
    if(pos<1 || pos >pArr->cnt)
    {
        return false;
    }
    *pval = pArr->pBase[pos - 1];
    for(i = pos; i < pArr->cnt; i++)
    {
        pArr->pBase[i - 1] = pArr->pBase[i];
    }
    (pArr->cnt)--;
    return true;
}


void Inversion_arr(Arr *pArr)
{
    int left = 0;
    int right = pArr->cnt - 1;
    int tmp = 0;
    while(left<right)
    {
        tmp = pArr->pBase[left];
        pArr->pBase[left] = pArr->pBase[right];
        pArr->pBase[right] = tmp;
        left++;
        right--;
    }
}

void Sort_arr(Arr *pArr)
{
    int i = 0;
    int j = 0;
    int tmp = 0;
    for (i = 0; i < pArr->cnt - 1; i++)
    {
        for (j = i + 1; j < pArr->cnt; j++)
        {
            if(pArr->pBase[i]>pArr->pBase[j])//升序
            {
                tmp = pArr->pBase[i];
                pArr->pBase[i] = pArr->pBase[j];
                pArr->pBase[j] = tmp;
            }
        }
    }
}