#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

//节点的数据类型
typedef struct Node
{
    int data;            //数据域
    struct Node *pNext;  //指针域
} * PNODE, NODE;  //PNODE 等价于struct Node *  NODE 等价于struct Node


//函数声明
PNODE creat_list(void);           //初始化
void traverse_list(PNODE pHead);  //输出
bool is_empty(PNODE pHead);       //判断是否为空
int length_list(PNODE pHead);    //求长度,有效节点的长度

//再pHead所指向的节点前面的第pos个节点的前面插入一个新的节点，该节点的值为val，并且pos从1开始
bool insert_list(PNODE pHead, int pos, int val);
bool delete_list(PNODE, int, int *);
void sort_list(PNODE);      //排序  


//主函数
int main()
{
    PNODE pHead = NULL;
    int length = 0;
    int val = 0;
    pHead = creat_list();   //创建非循环单链表
    traverse_list(pHead);   //遍历输出
    // if(is_empty(pHead))
    // {
    //     printf("链表为空!\n");
    // }
    // else
    // {
    //     printf("链表不为空！\n");
    // }
    length = length_list(pHead);
    printf("链表的长度是%d\n", length);
    sort_list(pHead);   //排序
    traverse_list(pHead);   //遍历输出

    // insert_list(pHead,1,123);
    // traverse_list(pHead);

    // if(delete_list(pHead,3,&val))
    // {
    //     printf("删除的元素是%d\n", val);
    // }
    // else
    // {
    //     printf("删除失败！\n");
    // }
    return 0;
}





//函数的定义
PNODE creat_list(void)
{
    int len = 0;
    int val = 0;
    int i = 0;
    //分配了一个不存放有效数据的头节点
    PNODE pHead = (PNODE)malloc(sizeof(NODE));
    if(NULL == pHead)
    {
        printf("分配失败，程序退出!\n");
        exit(-1);
    }
    //中转节点，永远指向最后一个节点
    PNODE pTail = pHead;
    pHead->pNext = NULL;
    //有有效数据的其他节点
    printf("请输入你需要生成的链表节点的个数:");
    scanf("%d", &len);
    for (i = 0; i < len; i++)
    {
        printf("请输入第%d个节点的值:", i + 1);
        scanf("%d", &val);
        PNODE pNew = (PNODE)malloc(sizeof(NODE));
        if(NULL == pNew)
        {
            printf("分配失败，程序退出!\n");
            exit(-1);
        }
        pNew->data = val;  //数据
        pNew->pNext = NULL;

        pTail->pNext = pNew;
        pTail = pNew;  //最后的节点发生改变
    }
    return pHead;
}

void traverse_list(PNODE pHead)
{
    // PNODE p = pHead->pNext;
    // while(NULL != p)
    // {
    //     printf("%d ", p->data);
    //     p = p->pNext;  //下一个节点
    // }
    // printf("\n");

    while (NULL != pHead->pNext)
    {
        printf("%d ", pHead->pNext->data);  //输出下一个节点的有效数据
        pHead = pHead->pNext;  //跳到下一个节点
    }
    printf("\n");
}


bool is_empty(PNODE pHead)
{
    if(pHead->pNext == NULL)
    {
        return true;  //为空
    }
    else 
    {
        return false;
    } 
}


int length_list(PNODE pHead)
{
    int len = 0;
    while (pHead->pNext != NULL)
    {
        len++;
        pHead = pHead->pNext;
    }
    return len;
}

//链表排序
void sort_list(PNODE pHead)
{
    int tmp = 0;
    PNODE p, q;
    for (p = pHead->pNext; p->pNext->pNext != NULL; p = p->pNext)  //比较到最后一个节点前一个节点
    {
        for (q = p->pNext; q->pNext != NULL; q = q->pNext) //最后一个节点
        {
            if (p->data > q->data)
            {
                tmp = q->data;
                q->data = p->data;
                p->data = tmp;
            }
        }
    }
    return;
}

//再pHead所指向的节点前面的第pos个节点的前面插入一个新的节点，该节点的值为val，并且pos从1开始
bool insert_list(PNODE pHead, int pos, int val)
{
    int i = 0;
    PNODE p = pHead;  //工具指针
    while(p!=NULL && i<pos-1)  //是否至少为pos位置前的第二个节点， !=NULL 进入循环跳到下一个节点
    {
        p = p->pNext;   //pos位置前一个节点，或者是最后一个节点的空指针
        i++;
    }
    if(i>pos-1 || p==NULL)  //pos之前的节点不存在（不一定是前一个）//i>pos-1判断pos是否大于0，在1，2，3..这些位置插入
    {
        return false;
    }
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if(pNew == NULL)
    {
        printf("分配空间失败，程序退出！\n");
        exit(-1);
    }
    pNew->data = val;
    pNew->pNext = p->pNext;
    p->pNext = pNew;

    return true;
}



bool delete_list(PNODE pHead, int pos, int *val)
{
    int i = 0;
    PNODE p = pHead;  //工具指针
    //起码要有首指针才能进行删除
    while(p->pNext!=NULL && i<pos-1)  //是否至少为pos位置前的第二个节点， !=NULL 进入循环跳到下一个节点,
    {
        p = p->pNext;   //pos位置前一个节点，或者是最后一个节点
        i++;
    }
    if(p->pNext==NULL || i<pos-1)  //pos位置的节点( 前一个节点->pNext==NULL )不存在 //i>pos-1判断pos是否大于0，在1，2，3..这些位置删除
    {
        return false;
    }

    PNODE pTail = NULL;
    *val = p->pNext->data;  //要删除的节点的数据
    pTail = p->pNext;  //留用释放，要删除的节点
    p->pNext = p->pNext->pNext; //后一个的节点取代要删除的节点
    //释放空间
    free(pTail);
    pTail = NULL;
    return true;
}