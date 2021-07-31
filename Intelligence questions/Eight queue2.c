#include<stdio.h>
#include<stdlib.h>

#define MAXNODE 8
#define ROW 8
#define COL 8
#define COUNT 8
typedef struct posnode
{
    int x;
    int y;
    int nums; //第几列开始
} PosNode;

PosNode Step[MAXNODE];
int top = -1;

int count = 0;  //第几种可能


//row,i位置是否可以落子
int notDanger(int row,int col,int chess[ROW][COL])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < ROW; i++)
    {
        if(chess[i][col]==1)
        {
            return 0;
        }
    }
    //左上
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    //右下
    for (i = row, j = col; i <=ROW && j < COL; i++, j++)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    //右上
    for (i = row, j = col; i >= 0 && j < COL; i--, j++)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    //左下
    for (i = row, j = col; i < ROW && j >= 0; i++, j--)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    return 1;
}

//栈的初始化
void initStep(void)
{
    int i = 0;
    for (i = 0; i < MAXNODE; i++)
    {
        Step[i].x = 0;
        Step[i].y = 0;
        Step[i].nums = 0;
    }
    top = -1;
}

//
void EightQueen()
{
    //第一行的第k列为第一个落子
    for (int k = 0; k < COL; k++)
    {
        initStep();
        //入栈
        top++;
        Step[top].x = 0;
        Step[top+1].y = k;   

        int chess[ROW][COL];
        int i = 0;
        int j = 0;
        for (i = 0; i < ROW; i++)
        {
            for (j = 0; j < COL; j++)
            {
                chess[i][j] = 0;
            }
        }
        chess[0][k] = 1;  //标记第一个落子

        //开始遍历查找
        while (top >= 0)
        {
            int num = 0;
            int lx = 0;
            int ly = 0;
            
            //没有落满八子
            if(top+1 != COUNT)
            {
                //找到第top+1行的第num个位置落子
                for (num = Step[top].nums; num < ROW; num++)
                {
                    Step[top].nums += 1;
                    //可以落子
                    if(notDanger(top+1,num,chess))
                    {
                        //入栈
                        top++;
                        Step[top].x = top;  
                        Step[top].y = num;
                        chess[top][num] = 1; //标记落子
                        break;
                    }
                }
            }
            //八个皇后落在棋盘
            if (COUNT == top+1)
            {
                printf("第 %d 种:\n",++count);
                for (i = 0; i < ROW; i++)
                {
                    for (j = 0; j < COL; j++)
                    {
                        printf("%d ", chess[i][j]);
                    }
                    printf("\n");
                }
                printf("\n");
            }    
            //是否回溯
            if(num == ROW || top == COUNT-1)
            {
                //出栈
                lx = Step[top].x;
                ly = Step[top].y;
                Step[top].nums = 0;
                chess[lx][ly] = 0;
                top--;
            }
        }
    }
}




int main()
{
    EightQueen();
    return 0;
}