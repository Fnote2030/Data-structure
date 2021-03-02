/*
    队列
*/

/*
    静态队列 -- 循环队列r
    由两个参数决定
    初始化 front == rear ==0
    font    代表的是队列的第一个元素r
    rear    代表的是队列的最后一个有效元素的下一个元素
 
    队列为空时 front==rear 但是不一定为0
*/
/*
    入队的伪算法
    1、将值存到r所代表的位置
    2、r=（r+1）%数组的长度

    出队的伪算法
    1、将f位置的值保存（根据自己的要求选择）
    2、f=（f+1）%数组的长度

    队列已满
    1、少用一个元素（数组的长度-1）  front和rear紧挨着 （（r+1）%数组长度 == front）
    2、添加一个变量标记，初始化为0，当入队之后，front==rear时，置为1，表示队列已满
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
#define MAX_QUEUE 6  //队列的大小，存放  MAX_QUEUE

typedef struct Queue
{
    int *pBase;
    int front;
    int rear;
} QUEUE, *PQUEUE;



//声明函数
void init_queue(PQUEUE pQ);
bool is_full(PQUEUE pQ);
bool is_empty(PQUEUE pQ);
bool en_queue(PQUEUE pQ, int val);
void traverse(PQUEUE pQ);   //打印
bool out_queue(PQUEUE pQ, int *val);

//主函数
int main()
{
    QUEUE Q;  //定义变量
    int val = 0;
    init_queue(&Q);
    en_queue(&Q, 20);
    en_queue(&Q, 120);
    en_queue(&Q, 212);
    en_queue(&Q, -238);

    traverse(&Q);
    if(out_queue(&Q,&val))
    {
        printf("出队的元素是%d\n", val);
    }
    else
    {
        printf("出队失败!队列为空!\n");
    }
    traverse(&Q);
    return 0;
}




//定义函数
void init_queue(PQUEUE pQ)
{
    pQ->pBase = (int *)malloc(sizeof(int) * MAX_QUEUE);
    if(pQ->pBase==NULL)
    {
        printf("开辟空间失败！\n");
        exit(-1);
    }
    pQ->rear = 0;
    pQ->front = 0;
}
bool is_full(PQUEUE pQ)
{
    if ((pQ->rear + 1) % MAX_QUEUE == pQ->front)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//进队
bool en_queue(PQUEUE pQ, int val)
{
    if(is_full(pQ))  //循环队列满了
    {
        return false;
    }
    else
    {
        pQ->pBase[pQ->rear] = val;  //将val的值存在rear的位置
        pQ->rear = (pQ->rear + 1) % MAX_QUEUE;   //rear向后加一
        return true;
    }
}

void traverse(PQUEUE pQ)
{
    if(is_empty(pQ))
    {
        printf("队列为空！\n");
        return;  //队列为空
    }
    int i = pQ->front;  //头部
    while(i!=pQ->rear)
    {
        printf("%d ", pQ->pBase[i]);
        i = (i + 1) % MAX_QUEUE;
    }
    printf("\n");
}

bool is_empty(PQUEUE pQ)
{
    if(pQ->front == pQ->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//出队
bool out_queue(PQUEUE pQ, int *val)
{
    if(is_empty(pQ))  //循环队列空的
    {
        return false;
    }
    else
    {
        *val = pQ->pBase[pQ->front];
        pQ->front = (pQ->front + 1) % MAX_QUEUE;
        return true;
    }
}