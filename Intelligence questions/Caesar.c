#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>

//个体的类型
typedef struct ElemType
{
    char ch;
} ElemType;
//个体关系的类型
typedef struct Node
{
    ElemType data;
    struct Node *prior;
    struct Node *next;
} Node, *PNode;




//函数的声明

bool InitList(PNode *pHead);
PNode Caesar(PNode pHead, int val);



//主函数
int main()
{
    PNode pHead;
    int n = 0;
    int i = 0;
    InitList(&pHead);
    while(1)
    {
        printf("请输入一个整数：");
        scanf("%d", &n);
        PNode p = Caesar(pHead, n);
        for (i = 0; i < 26; i++)
        {
            printf("%c", p->data.ch);
            p = p->next;
        }
        printf("\n\n");
    }
    return 0;
}

PNode Caesar(PNode pHead, int val)
{
    PNode p = pHead;
    if(val<0)
    {
        while((p=p->prior,++val))
        {
            ;
        }
    }
    if(val>0)
    {
        while((p=p->next,--val))
        {
            ;
        }
    }
    return p;
}

bool InitList(PNode *pHead)
{
    PNode p, pnew;
    int i;
    *pHead = (PNode)malloc(sizeof(Node));
    if((*pHead) == NULL)
    {
        return false;
    }

    (*pHead)->prior = (*pHead)->next = NULL;
    p = (*pHead);  //永远指向新节点

    for (i = 0; i < 26; i++)
    {
        pnew = (PNode)malloc(sizeof(Node));
        if(pnew == NULL)
        {
            return false;
        }
        pnew->data.ch = 'A' + i;
        pnew->next =(*pHead)->next;
        pnew->prior = p;
        p->next = pnew;

        p = pnew;  //指向新节点
    }
    (*pHead)->next->prior = p;
    free(*pHead);
    (*pHead) = p->next;
    return true;
}
