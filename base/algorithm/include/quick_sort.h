#pragma once
#include <iostream>
using namespace std;
// 快速排序 基准点， 分区

void quick_sort(int (&)[10], int, int);
// 按照支点分区函数
int partition(int (&)[10], int, int);
void swap(int (&)[10], int, int);
void print_arr(int arr[], int size);

void quick_sort(int (&arr)[10], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = partition(arr, start, end);

    // 递归调用，分别对2部分继续排序
    quick_sort(arr, start, mid - 1);
    quick_sort(arr, mid + 1, end);
}

int partition(int (&arr)[10], int start, int end)
{
    // 选取支点
    int pivot = arr[start];

    // 指定指向数组的头尾元素的“指针”
    int left = start, right = end;

    // 左右指针没有相遇，继续移动
    while (left < right)
    {
        // 左指针不断有右移，直到找到比支点大的值
        while (arr[left] <= pivot && left < right)
        {
            left++;
        }
        // 右指针不断有左移，直到找到比支点小的值
        while (arr[right] >= pivot && left < right)
        {
            right--;
        }
        // 左右互换
        swap(arr, left, right);
    }
    // 判断指针相遇位置的值，跟支点大小
    if (arr[left] <= pivot)
    {
        // 比支点值小，直接换到头位置
        swap(arr, start, left);
        return left;
    }
    else if (arr[left] > pivot)
    {
        // 比支点值大，就将前一个位置放到数组头位置
        swap(arr, start, left - 1);
        return left - 1;
    }
}
// 交互
void swap(int (&arr)[10], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void test_quick_soft()
{
    int arr[10] = {33, 1, 55, 32, 22, 11, 15, 78, 34, 32};
    int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, size - 1);

    print_arr(arr, size);
}

void print_arr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}
