/*
        动态队列
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>

typedef struct Node
{
    char s[10];
    int h;   //不在位将牌数
    int g;   //从初始节点s到当前节点n的耗散值
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
bool en_queue(PQUEUE pQ, char *s, int h , int g); //进队
void traverse(PQUEUE pQ);   //遍历打印
bool out_queue(PQUEUE pQ, char (*s)[10], int *h, int *g); //出队
//求得节点的h值
int numofh(char *s);
void eight_digital(PQUEUE open, PQUEUE closed, char *digital);
//生成拓展节点的信息
bool movedigital(char *s, int n,int j);
bool notfind(PQUEUE pQ, char *s);

int main()
{
    char digital[10] = {};//初始化为0
    PQUEUE closed = (PQUEUE)malloc(sizeof(QUEUE));
    PQUEUE open = (PQUEUE)malloc(sizeof(QUEUE));


    printf("请输入9个字符的字符串(0-8):");
    scanf("%s", digital);
    eight_digital(open,closed,digital); //开始移动
    traverse(closed);

    return 0;
}


void eight_digital(PQUEUE open, PQUEUE closed, char *digital)
{
    init_queue(open);
    init_queue(closed);

    en_queue(open, digital, numofh(digital), 0); //首节点进队

    char s[10]={};  //节点字符串信息

    while (1)
    {
        //open 出队 closed 入队 
        int num = 0;//刚出队列节点的h值
        int g = 0;  //刚出队列节点的g值
        out_queue(open, &s, &num, &g);
        en_queue(closed, s, num, g);
        if(num == 0)  
            break; //不在位的将牌数,为0时到达目标状态，退出移动

        //生成新的节点
        int i = 0;
        int j = 0;
        char s1[10], s2[10], s3[10], s4[10];
        char *sa[4]={s1,s2,s3,s4};  //指针数组
        int sah_num[4] = {0};//扩展节点的h值,初始化为0
        for (i = 0; i < 4; i++)//四个方向上的节点
        {
            
            strcpy(sa[i], s);//至多四个拓展节点
            for (j = 0; j < 9; j++)//找到空格的位置
            {
                if(s[j] == '0')
                    break;
            }
            //生成扩展节点
            if(movedigital(sa[i], i, j))  //i--方向 j--原位置
                sah_num[i] = numofh(sa[i]);//求得h值
            else
                sah_num[i] = 9;
        }
        //按照h（按照h（不在位的将牌数）大小进队，h小的先进队
        for (j = 0; j < 4; j++)//至多比较四趟
        {
            int hnum_max = 9;  //不在位的将牌数
            int a = -1;   //记录第一个进队的节点
            for (i = 0; i < 4; i++)
            {
                if(sah_num[i] <= hnum_max && sah_num[i] <= num && notfind(closed,sa[i]))//num是小于等于8的,不在closed表中
                {
                    hnum_max = sah_num[i];
                    a = i;
                }
            }
            if(a>=0)//找到了符合要求的节点
            {
                en_queue(open,sa[a],sah_num[a]);
                sah_num[a] = 9;  
            }
            else  //没有找到，下次循环也找不到
                break;
        }
    }
}


bool movedigital(char *s, int n,int j)
{
    //左上右下搜索
    int fangxiang[4] = {-1,-3,1,3};
    int newone = j + fangxiang[n];
    if (newone < 9 && newone > 0 && (newone / 3 == j / 3 || newone % 3 == j % 3))//不换行||不换列，不越界
    {
        s[j] = s[newone];
        s[newone] = '0';
        return true;
    }
    else
    {
        return false;
    }
}

int numofh(char *s)
{
    int num = 8;
    int i = 0;
    char ss[9] = {'1', '2', '3', '8', '0', '4', '7', '6', '5'};
    for (i = 0; i < 9; i++)
    {
        if (s[i] == ss[i] && i!=4)
            num--;
    }
    return num;
}



//函数的定义
void init_queue(PQUEUE pQ)
{
    PNODE p = (PNODE)malloc(sizeof(NODE));//创建节点
    if(p==NULL)
    {
        printf("分配空间失败1！\n");
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

bool en_queue(PQUEUE pQ, char *s, int h, int g)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if(pNew==NULL)
    {
        printf("分配空间失败2！\n");
        return false;
    }
    else
    {
        strcpy(pQ->rear->s, s);
        pQ->rear->h = h;
        pQ->rear->g = g;
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
        printf("队列为空1!\n");
    }
    else
    {
        PNODE p = pQ->front;  //指向头节点
        while(p != pQ->rear)
        {
            printf("%s\n", p->s);
            p = p->pNext;
        }
        printf("\n");
    }
}

bool out_queue(PQUEUE pQ, char (*s)[10], int *h, int *g)
{
    if(is_empty(pQ))
    {
        printf("队列为空2!\n");
        return false;
    }
    else
    {
        PNODE p = pQ->front->pNext; //暂存
        strcpy(*s, pQ->front->s);    //头节点的数据
        *h = pQ->front->h;
        *g = pQ->front->g;
        free(pQ->front);        //释放头节点的空间
        pQ->front = p;    
        return true;
    }
}


bool notfind(PQUEUE pQ, char *s)
{
    if(is_empty(pQ))
    {
        printf("队列为空3!\n");
        return true;
    }
    else
    {
        PNODE p = pQ->front;  //指向头节点
        while(p != pQ->rear)  //遍历所有节点 头->尾
        {
            if(strcmp(p->s,s) == 0)
                return false;
            p = p->pNext;
        }
        return true;
    }
}