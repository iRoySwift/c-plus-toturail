#pragma once
#include <iostream>

// void increment(int &value);
// void increment(int *value);
// void print_arr(int arr[]);
// void print_arr(int *arr, int size);

// 使用引用传递
void increment(int &value)
{
    value++;
    std::cout << "引用传递增量后值: " << value << std::endl;
}
// 使用指针传递
void increment(int *value)
{
    (*value)++;
    std::cout << "指针传递增量后值: " << *value << std::endl;
}

// 使用指针传递数组
// int arr[] = int *arr
// void print_arr(int arr[])
// {
// }

void print_arr(int *arr, int size)
{
    std::cout << "*arr:" << arr << std::endl;
    std::cout << "指针传递值打印: ";
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <size_t N>
// 使用引用传递数组
void print_arr(int (&arr)[N])
{
    std::cout << "引用传递值打印: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
