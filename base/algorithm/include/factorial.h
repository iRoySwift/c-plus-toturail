#ifndef FACTORIAL_H
#define FACTORIAL_H

// 阶乘函数，递归
inline int factorial(int n)
{
    if (n <= 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

#endif // FACTORIAL_H
