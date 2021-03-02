/*
        动态队列
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>


typedef struct Node
{
    int data;
    struct Node *pNext;
} NODE, *PNODE;

typedef struct Queue
{
    PNODE front;
    PNODE rear;
} QUEUE, *PQUEUE;



//声明函数
void init_queue(PQUEUE pQ);   //初始化，创建
bool is_empty(PQUEUE pQ);   
bool en_queue(PQUEUE pQ, int val); //进队
void traverse(PQUEUE pQ);   //遍历打印 
bool out_queue(PQUEUE pQ, int *val);//出队
 

int main()
{
    int val = 0;
    QUEUE Q;
    init_queue(&Q);  //
    en_queue(&Q, 12);
    en_queue(&Q, -212);
    en_queue(&Q, 43);
    traverse(&Q);   //遍历打印

    if(out_queue(&Q,&val))
    {
        printf("出队的元素是%d\n", val);
    }
    else
    {
        printf("出队失败！队列为空!\n");
    }

    en_queue(&Q, 456);
    traverse(&Q);
    return 0;
}



//函数的定义
void init_queue(PQUEUE pQ)
{
    PNODE p = (PNODE)malloc(sizeof(NODE));//创建节点
    if(p==NULL)
    {
        printf("分配空间失败！\n");
        exit(-1);
    }
    else
    {
        //p->data = 0;   //随便赋值，不赋值也行
        p->pNext = NULL;//还没有pNext
        pQ->front = p;
        pQ->rear = p;
    }
}

bool en_queue(PQUEUE pQ,int val)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if(pNew==NULL)
    {
        printf("分配空间失败！\n");
        return false;
    }
    else
    {
        pQ->rear->data = val;  //在尾节点插入数据
        pQ->rear->pNext = pNew; //链接新节点
        pNew->pNext = NULL;
        pQ->rear = pNew;      //新节点为尾节点
        return true;
    }
}

bool is_empty(PQUEUE pQ)
{
    if(pQ->rear == pQ->front)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void traverse(PQUEUE pQ)
{
    if(is_empty(pQ))
    {
        printf("队列为空!\n");
    }
    else
    {
        PNODE p = pQ->front;  //指向头节点
        while(p != pQ->rear)
        {
            printf("%d ", p->data);
            p = p->pNext;
        }
        printf("\n");
    }
}


bool out_queue(PQUEUE pQ, int *val)
{
    if(is_empty(pQ))
    {
        printf("队列为空!\n");
        return false;
    }
    else
    {
        // PNODE p = pQ->rear;
        // *val = p->data;
        // pQ->rear = p->pNext;
        // free(p);
        // p == NULL;
        PNODE p = pQ->front->pNext; //暂存
        *val = pQ->front->data;    //头节点的数据
        free(pQ->front);        //释放头节点的空间
        pQ->front = p;
        return true;
    }
}