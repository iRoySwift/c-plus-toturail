#include <iostream>

int main()
{
    int *p1;
    long *p2;
    std::cout << "p1内存大小: " << sizeof(p1) << ", p1地址: " << p1 << std::endl;
    std::cout << "p2内存大小: " << *p2 << ", p2地址: " << p2 << std::endl;
    return 0;
}
