#include<stdio.h>

//插入排序
void insert_sort(int *arr,int sz)
{
    int i = 0;
    int j = 0;
    int cur;
    for (i = 1; i < sz; i++)
    {
        cur = arr[i];
        for (j = i-1; j >= 0; j--)
        {
            if(cur >= arr[j])
            {
                break;
            }
            else
            {
                arr[j+1] = arr[j]; //向后移动
            }
        }
        arr[j+1] = cur;
    }
}


int main()
{
    int arr[] = {3,4,54,-23,54,23,67,26,-34,0,12};
    int sz = sizeof(arr) / sizeof(*arr);
    insert_sort(arr, sz);
    int i = 0;
    for (i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}