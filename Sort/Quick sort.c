#include<stdio.h>
#include<stdlib.h>

int count = 0;
int Findpos(int *a,int low,int high)
{
    int val = a[low];
    while(low<high)
    {
        while(low<high && a[high]>=val)
        {
            --high;
        }
        //右边的小于val,停止移动，并将值赋给左边
        a[low] = a[high];  
        while(low<high && a[low]<=val)
        {
            ++low;
        }
        //左边的大于val,停止移动，并将值赋给右边
        a[high] = a[low];
    }
    a[low] = val;
    return low;
}


void quicksort(int *a,int low,int high)
{
    count++;
    int pos = 0;
    if(low<high)
    {
        pos = Findpos(a, low, high);
        quicksort(a, low, pos - 1);
        quicksort(a, pos + 1, high);
    }
}


//时间复杂度为O(nlogn)
int main()
{
    int arr[10] = {121,54,44,34,23,12,0,-12,-124,-141,-342};
    int i = 0;
    quicksort(arr, 0, 9);
    for (i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%d\n", count);
    return 0;
}

