#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


typedef struct Node
{
    int data;
    char name;
    struct Node *next;
}Node,*PNode;


//创建一个循环链表，每个节点赋予任意的值，创建好之后返回第一个节点
PNode creat()
{
    int count = 0;
    int len = 0;
    PNode pHead = (PNode)malloc(sizeof(Node));
    if(pHead == NULL)
    {
        printf("分配空间失败!\n");
        exit(-1);
    }
    else
    {
        PNode pHead = (PNode)malloc(sizeof(Node));
        PNode p = pHead;   //中转节点

        printf("请输入要设置的节点个数:");
        scanf("%d", &count);
        
        while(len < count)
        { 
            PNode pnew = (PNode)malloc(sizeof(Node));
            printf("请输入第%d个节点的轮询值:", ++len);
            scanf("%d", &(pnew->data));
            pnew->name = '@' + len;
            p->next = pnew;
            p = pnew;
        }
        p->next = pHead->next;   //最新一个节点链接到第一个节点
        free(pHead);
        pHead->next = NULL;
        return p->next;
    }
}

//第一个节点的data作为报数次数len，顺时针报数，报到n的淘汰，并将它的data作为新的报数次数len,直到剩余一个
void start(PNode pHead)
{
    PNode p;
    while(pHead->next != pHead)
    {
        int len = pHead->data;
        //定位到要淘汰节点的前一个节点
        while(--len)
        {
            pHead = pHead->next;
        }
        printf("%c(val=%d) >> ", pHead->next->name,pHead->next->data);
        p = pHead->next;  //暂停要淘汰的节点
        pHead->next =p->next; //前一个链接到下一个
        free(p);
        p->next = NULL;

        pHead = pHead->next;  //从淘汰节点的下一个节点重新开始
    }
    printf("%c(val=%d)\n", pHead->next->name,pHead->next->data);
}

int main()
{
    PNode p = creat();   //创建循环链表，返回第一个节点
    printf("淘汰顺序为：\n");
    start(p);
    return 0;
}