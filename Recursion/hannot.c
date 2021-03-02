#include<stdio.h>
/*
    汉诺塔
*/



//x移动开始位置 y中转位置 z目的位置
int movehannot(int num,char x,char y,char z)
{
    int len = 0;
    if(1 == num)
    {
        printf("%-5d%c >> %c\n", num, x, z); //将num从x移动到z
        return 1;
    }
    else
    {
        len += movehannot(num - 1, x, z, y);        //将num-1这个整体从x移动到y上
        printf("%-5d%c >> %c\n", num, x, z); //将num从x移动到z
        len++;
        len += movehannot(num - 1, y, x, z);        //将num-1这个整体从y移动到z上
        return len;
    }
}


int main()
{
    int len = movehannot(4,'a','b','c');
    printf("一共要移动%d次\n", len);
    return 0;
}