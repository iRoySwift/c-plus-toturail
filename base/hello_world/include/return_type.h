// 返回数组指针
#ifndef RETURN_TYPE_H
#define RETURN_TYPE_H

int arr[5] = {1, 2, 3, 4, 5}; // 数组
int *pa[5];                   // 指针数组,pa是包含5个int 指针的数组
int (*ap)[5];                 // 数组指针，ap是一个指针,指向长度为5的int数组

// 函数声明，fun返回值类型为数组指针
int (*fun1(int x))[5]
{
    return &arr;
}

typedef int arrayT[5]; // 类型别名，arrayT代表长度为5的int数组
arrayT *fun2();        // fun2的返回类型是指向arrayT的数组指针

auto fun3() -> int (*)[5] // 尾置返回类型，返回数组指针
{
}

// 阶乘函数，递归
int factorial(int n) {
    if(n <= 0) {
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

#endif // RETURN_TYPE_H
