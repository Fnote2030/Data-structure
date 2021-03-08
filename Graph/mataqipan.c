#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Row 8
#define Col 8
#define maxStep 64

typedef struct {
    int abscissa;  //横坐标
    int ordinate;  //纵坐标
    int direction;  //方向
}SqStack;

int ChessBoard[Row+1][Col+1]={}; //储存路径的棋盘

//分别有（1 ~ 8）个方向
int HTry1[8]={1, -1, -2, 2, 2, 1, -1, -2};
int HTry2[8]={2, -2, 1, 1, -1, -2, 2, -1};

SqStack PointStack[maxStep];
int top = -1; //栈顶

int flagOperate = 0; //操作标记
int num = 0;  //记录结果数

void printChessBoard() {
    printf("棋盘路径是:\n");
    for(int i = 1;i <= Row;i++) {
        for(int j = 1;j <= Col;j++) {
            printf("%4d ", ChessBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

//入栈
void push(int abscissa, int ordinate) {
    ++top;
    PointStack[top].abscissa = abscissa;
    PointStack[top].ordinate = ordinate;
    PointStack[top].direction = -1; //初始化方向
}

//出栈
void pop() {
    PointStack[top].abscissa = 0;
    PointStack[top].ordinate = 0;
    PointStack[top].direction = -1; //初始化方向
    --top;
}

//打印栈
void printStack() {
    printf("目前栈的情况:\n");
    for(int i = 0;i < maxStep;i++) {
        printf("x:%d , y:%d, d:%d\n", PointStack[i].abscissa, PointStack[i].ordinate, PointStack[i].direction);
    }
    printf("\n\n");
}

//标记棋盘 落子
void markChessBoard(int abscissa, int ordinate) {
    ChessBoard[ordinate][abscissa] = top+1;
}


void runChessBoard() {
    int xNow, yNow; //当前马所在的坐标
    
    while(1) {  //一次循环落一子
        
        if(flagOperate == 1) {
            if(top == maxStep - 1) { //落满64子
                printChessBoard();
                break;     
            }
        }else if(flagOperate == 2 ) {
            if(top == maxStep - 1){
                printf("%d \n\n", ++num);
                printChessBoard();
            }
        }
        
        
        //当前位置
        xNow = PointStack[top].abscissa;
        yNow = PointStack[top].ordinate;
        
        //贪心算法的前置资源
        int count[8] = {0};
        for(int i = 0;i < 8;i++)
        {
            int xNext = xNow, yNext = yNow;
            //下一个落子位置
            xNext += HTry1[i];
            yNext += HTry2[i];
            //判断是否可以落子 1、在棋盘范围内 2、位置是空的
            if(xNext > 0 && xNext <= Col && yNext > 0 && yNext <= Row && ChessBoard[yNext][xNext] == 0) 
            {
                count[i]++;
                for(int j = 0;j < 8;j++) 
                {
                    int xNextNext = xNext, yNextNext = yNext;
                    //落子位置的出口位置
                    xNextNext += HTry1[j];
                    yNextNext += HTry2[j];

                    if(xNextNext > 0 && xNextNext <= Col  && yNextNext > 0 && yNextNext <= Row && ChessBoard[yNextNext][xNextNext] == 0) 
                    {
                        count[i]++;  //位置i的出口加一
                    }
                }
            }
        }

        
        //对八个方向进行排序，实际要走的方向记录在directionNext中
        int directionNext[8] = {};
        int temp = 9;
        int  k = 0;
        for(int i = 0;i < 8;i++) {
            temp = 9;
            for(int j = 0;j < 8;j++) {
                if(count[j]<temp){
                    directionNext[i] = j;
                    temp = count[j];
                    k = j;
                }
            }
            count[k] = 9;   
        }
        
        //走下一步
        int direnow = 0;
        //没走过的位置开始试
        for(direnow = PointStack[top].direction + 1 ; direnow < 8 ; direnow++) {
            int xRealNext = xNow, yRealNext = yNow;
            xRealNext += HTry1[directionNext[direnow]];
            yRealNext += HTry2[directionNext[direnow]];
            PointStack[top].direction += 1;
            //位置是否能走
            if(xRealNext <= Col && xRealNext > 0 && yRealNext <= Row && yRealNext > 0 &&ChessBoard[yRealNext][xRealNext] == 0) 
            {
                push(xRealNext, yRealNext);
                markChessBoard(xRealNext, yRealNext);
                break;
            }
        }
        
        //判断无路可走出栈
        if(PointStack[top].direction >= 7) 
        {
            int x, y;
            x = PointStack[top].abscissa;
            y = PointStack[top].ordinate;
            ChessBoard[y][x] = 0; //棋盘标记取消
            pop();
        }
    }
}

void InitStartPoint() {
    int x, y;
    
    //输入起始坐标点
    printf("请输入起始点（x，y）:");
    scanf("%d %d", &x, &y);
    printf("请输入需要运算的方式：\n  1.找出一个结果\n  2.找出所有结果(几乎不可能)\n输入:");
    scanf("%d", &flagOperate);
    while(((x > Col||x <= 0)&&(y > Row||y <= 0))||(flagOperate <= 0 && flagOperate >= 3)) {
        if((x > Col||x <= 0)&&(y > Row||y <= 0)) {
            printf("输入的坐标超出范围，请重新输入（0~8）：");
            scanf("%d %d", &x, &y);
        }else if(flagOperate <= 0 && flagOperate >= 3) {
            printf("输入错误，请重新输入：\n");
            printf("请输入需要运算的方式：\n  1.找出一个结果\n  2.找出所有结果(几乎不可能)\n输入:");
            scanf("%d", &flagOperate);
        }
    }
    
    //入首栈
    push(x, y);
    markChessBoard(x, y);
}

int main() {
    InitStartPoint();
    clock_t start,finish; //开始结束时间
    double duration;  //运行用时
    start = clock();
    runChessBoard();
    finish = clock();
    duration = (double) (finish - start) / CLOCKS_PER_SEC;
    printf("运行用时: %f second\n", duration);
}