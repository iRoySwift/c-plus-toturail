#pragma once
#include <iostream>
#include <vector>
using namespace std;
// 二分法, 要求数组事先排好序

// 传引用 (const vector<int>&)，避免复制，同时保留长度信息
int binary_search(const std::vector<int> &arr, int start, int end, int target)
{
    // ... 逻辑不变，但 arr.size() 可以用了 ...
}

// 指针 下面写法一样  灵活性：极高。它可以接收任何长度的 int 数组。
int binary_search(int arr[]);
int binary_search(int *arr);

// 引用 灵活性：极低。它只能接收特定长度的数组。
int binary_search(const int (&arr)[6], int start, int end, int target)
{
    // 基准判断，没有元素了，或者target超出范围，返回-1
    if (start > end || arr[start] > target || arr[end] < target)
    {
        return -1;
    }
    // 中间位置
    int mid = (start + end) / 2;

    // 比较中间位置值
    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] > target)
    {
        return binary_search(arr, start, mid - 1, target); // 中间位置大，搜前半部分
    }
    else
    {
        return binary_search(arr, mid + 1, end, target); // 搜前后部分
    }
}

int test_binary_search()
{
    int arr[6] = {1, 2, 10, 34, 55, 99};
    int size = sizeof(arr) / sizeof(arr[0]);
    int i = binary_search(arr, 0, size, 55);
    std::cout << "55 位置： " << i << endl;
}
