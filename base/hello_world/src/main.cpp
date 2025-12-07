
#include <iostream>
#include <fstream>

struct Person
{
    int id;
    char name[50];
    double salary;
};

void binaryFileIO()
{
    Person p = {1, "John Doe", 50000.0};

    // 二进制写入
    std::ofstream out("data.bin", std::ios::binary);
    out.write(reinterpret_cast<char *>(&p), sizeof(Person));
    out.close();

    // 二进制读取
    Person p2;
    std::ifstream in("data.bin", std::ios::binary);
    in.read(reinterpret_cast<char *>(&p2), sizeof(Person));
    in.close();
}

int main()
{
    binaryFileIO();
    return 0;
}
