#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char s[10];
    int fx;    //记录该节点怎样变换来的
    struct Node *pNext;
} NODE, *PNODE;


typedef struct Stack
{
    PNODE pTop;      //永远指向栈顶元素
    PNODE pBottom;  //栈底元素下一个是没有实际含义的元素
} STACK, *PSTACK;


//函数的声明

//初始化栈
void initStack(PSTACK ps); 
//压栈
bool pushStack(PSTACK ps, char *s, int fx);  
//出栈一次，成功返回true，失败返回false
bool pop(PSTACK ps, char *s);           
//判断是否为空栈
bool is_empty(PSTACK ps); 
//释放栈
void clear(PSTACK ps); 
//求得节点的h值
int numofh(char *s);  
void eight_digital(char *digital);
//生成拓展节点的信息
bool change_digital(char *s, int n,int j);


int main()
{
    char digital[10] = {};//初始化为0
    printf("请输入9个字符的字符串(0-8):");
    scanf("%s", digital);
    eight_digital(digital); //开始搜索

    return 0;
}




void eight_digital(char *digital)
{
    PSTACK close = (PSTACK)malloc(sizeof(STACK));
    initStack(close);
    pushStack(close, digital, 4);//首节点入栈
    char s[10]={};  //节点字符串信息
    strcpy(s, digital);

    while (numofh(s))//不在位的将牌数,为0时到达目标状态，退出变换
    {
        //出栈打印
        int num = 0;//刚出栈节点的h值
        pop(close, s);
        printf("%s\n", s);
        num = numofh(s);  

        //生成新的节点，按照h（不在位的将牌数）大小入栈，h大的先入栈
        int i = 0;
        int j = 0;
        char s1[10], s2[10], s3[10], s4[10];
        char *sa[4]={s1,s2,s3,s4};  //指针数组
        int sah_num[4] = {0};//扩展节点的h值,初始化为0

        for (i = 0; i < 4; i++)//四个方向上的节点
        {
            if (((close->pTop->fx + 2) % 4) != i) //该方向的状态不是父节点
            {
                strcpy(sa[i], s);//至多四个拓展节点
                for (j = 0; j < 9; j++)//找到空格的位置
                {
                    if(s[j] == '0')
                        break;
                }
                //生成扩展节点
                if(change_digital(sa[i], i, j))
                    sah_num[i] = numofh(sa[i]);//求得h值
                else
                    sah_num[i] = 9;
            } 
            else
            {
                sah_num[i] = 9;
            }   
        }
        //按照h（不在位的将牌数）大小入栈，h大的先入栈
        int hnum_max = 0;
        int a = -1;
        for (j = 0; j < 4; j++)
        {
            for (i = 0; i < 4; i++)
            {
                if(sah_num[i] >= hnum_max && sah_num[i] <= num)
                {
                    hnum_max = sah_num[i];
                    a = i;
                }
            }
            if(a>=0)//找到了符合要求的节点
            {
                sah_num[i] = 9;
                pushStack(close,sa[a],a);
            }
            else  //没有找到，下次循环也找不到
                break;
        }
    }
    clear(close);//释放栈
    free(close);
}


bool change_digital(char *s, int n,int j)
{
    //左上右下搜索，下右上左生成
    int fangxiang[4] = {3,1,-3,-1};
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
    int num = 9;
    int i = 0;
    char ss[9] = {'1', '2', '3', '8', '0', '4', '7', '6', '5'};
    for (i = 0; i < 9; i++)
    {
        if (s[i] == ss[i])
            num--;
    }
    return num;
}

//函数的定义
void initStack(PSTACK ps)
{
    PNODE p = (PNODE)malloc(sizeof(NODE));
    if (NULL == p)
    {
        printf("分配空间失败！\n");
        exit(-1);
    }
    //printf("初始化成功！\n");
    p->pNext = NULL;
    ps->pBottom = p;
    ps->pTop = p; 

    
}

bool pushStack(PSTACK ps, char *s,int fx)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (NULL == pNew)
    {
        printf("分配空间失败！\n");
        return false;
    }
    strcpy(pNew->s,s);  //赋值
    pNew->fx = fx;
    pNew->pNext = ps->pTop;  //加在栈顶上面
    ps->pTop = pNew;        //栈顶为新节点
    //printf("压栈成功！\n");
    return true;
}


bool is_empty(PSTACK ps)
{
    if(ps->pBottom == ps->pTop)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool pop(PSTACK ps, char *s)
{
    if(is_empty(ps))
    {
        return false;
    }
    else
    {
        PNODE p = ps->pTop;  //栈顶
        strcpy(s, ps->pTop->s);
        ps->pTop =p->pNext;  //新栈顶
        free(p);
        p = NULL;
        return true;
    }
}


void clear(PSTACK ps)
{
    if(is_empty(ps))
    {
        return;
    }
    else
    {
        PNODE p;  //中转新的栈顶
        while(ps->pTop != ps->pBottom)
        { 
            p = ps->pTop->pNext;  //暂存新的栈顶
            free(ps->pTop); //释放原栈顶
            ps->pTop = p;
        }
    }

}