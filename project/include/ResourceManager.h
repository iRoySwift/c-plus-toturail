#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <stdexcept>
#include <memory>
#include <cstdio>

class FileRAII
{
    std::fstream file;

public:
    FileRAII(const char *filename, std::ios::openmode mode) : file(filename, mode)
    {
        if (!file.is_open())
        {
            throw std::runtime_error("无法打开文件");
        }
        std::cout << "文件已打开: " << filename << std::endl;
    };
    ~FileRAII()
    {
        if (file.is_open())
        {
            file.close();
            std::cout << "文件已关闭" << std::endl;
        }
    };
    void write(const std::string &content)
    {
        file << content;
        std::cout << "文件已写入" << std::endl;
    };
};

struct FileDeleter
{
    void operator()(FILE *fp) const
    {
        if (fp)
        {
            fclose(fp);
            std::cout << "文件已关闭（自定义删除器）" << std::endl;
        }
    }
};

class ResourceManager
{
    std::mutex mtx; // 每个 ResourceManager 实例持有自己的互斥锁

public:
    ResourceManager() = default;

    // 进程内互斥：保护文件操作
    void demonstrateRAII()
    {
        std::lock_guard<std::mutex> lock(mtx);
        FileRAII file("test.txt", std::ios::out);
        file.write("test raii");
    }

    void demonstrateCustomDeleter()
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::unique_ptr<FILE, FileDeleter> file_ptr(fopen("test.txt", "w"));
        if (file_ptr)
        {
            fprintf(file_ptr.get(), "自定义删除器示例\n");
        }
    }
};

int test_raii()
{
    ResourceManager manager;
    // 测试RAII
    manager.demonstrateRAII();
    // 测试自定义删除器
    manager.demonstrateCustomDeleter();
    return 0;
}
