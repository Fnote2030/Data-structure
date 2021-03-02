#include<stdio.h>
#include<stdlib.h>

int count = 0;


//row,i位置是否可以落子
int notDanger(int row,int col,int chess[8][8])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 8; i++)
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
    for (i = row, j = col; i <=8 && j < 8; i++, j++)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    //右上
    for (i = row, j = col; i >= 0 && j < 8; i--, j++)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    //左下
    for (i = row, j = col; i < 8 && j >= 0; i++, j--)
    {
        if(chess[i][j]==1)
        {
            return 0;
        }
    }
    return 1;
}


//row落子第几行
//n一共几行
void EightQueen(int row,int n,int chess[8][8])
{
    int chess2[8][8];
    int i = 0;
    int j = 0;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            chess2[i][j] = chess[i][j];
        }
    }
    //八个皇后落在棋盘
    if(8 == row)
    {
        printf("第 %d 种:\n",++count);
        for (i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                printf("%d ", chess2[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    else //没有落满八个皇后
    {
        //第row行的第几个位置
        for (i = 0; i < n; i++)
        {
            //可以落子
            if(notDanger(row,i,chess2))
            {
                //该行清零
                for (j = 0; j < 8; j++)
                {
                    chess2[row][j] = 0;
                }
                chess2[row][i] = 1;
                EightQueen(row + 1, n, chess2);
            }
        }
    }
    
}




int main()
{
    int chess[8][8];
    int i = 0;
    int j = 0;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            chess[i][j] = 0;
        }
    }
    EightQueen(0, 8, chess);
    return 0;
}