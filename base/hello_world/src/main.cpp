#include <iostream>
#include "../include/parameters.h"

int main()
{
    int i1 = 0;
    int i2 = i1;
    i2 = 1;
    std::cout << "i1: " << i1 << ", i2: " << i2 << std::endl;

    int &i3 = i1;
    i3 = 2;
    increment(i1);
    increment(&i3);
    std::cout << "i1: " << i1 << ", i3: " << i3 << std::endl;
    int *p1;
    long *p2;
    std::cout << "p1内存大小: " << sizeof(p1) << ", p1地址: " << p1 << std::endl;
    std::cout << "p2内存大小: " << sizeof(p2) << ", p2地址: " << p2 << std::endl;

    int arr[] = {1, 2, 3, 4, 5};
    print_arr(arr);
    print_arr(arr, (int)(sizeof(arr) / sizeof(arr[0])));
    return 0;
}
