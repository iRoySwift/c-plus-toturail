#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "../include/StudentManager.h"
using namespace std;

// Student 类和 StudentManager 的实现
void StudentManager::addStudent(unique_ptr<Student> student)
{
    students.push_back(move(student));
}

void StudentManager::displayAll() const
{
    if (students.empty())
    {
        cout << "没有学生信息。" << endl;
        return;
    }
    for (const auto &student : students)
    {
        student->display();
    }
}

Student *StudentManager::findStudent(const string &id) const
{
    for (const auto &student : students)
    {
        // 假设 Student 类有一个 getId() 方法
        if (student->getId() == id) // 这里应改为 student->getId() == id
        {
            return student.get();
        }
    }
    return nullptr;
}

int main()
{
    StudentManager manager;

    // 测试代码
    try
    {
        auto student1 = make_unique<Student>("张三", 20, "2024001");
        manager.addStudent(move(student1));
        auto student2 = std::make_unique<Student>("李四", 22, "2024002");
        manager.addStudent(std::move(student2));

        manager.displayAll();

        // 测试查找功能
        if (auto found = manager.findStudent("2024001"))
        {
            cout << "找到学生: " << found->getName() << endl;
        }

        // 测试查找不存在的学生
        if (auto found = manager.findStudent("999999"))
        {
            std::cout << "找到学生: " << found->getName() << std::endl;
        }
        else
        {
            cout << "未找到学号为999999的学生" << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "错误: " << e.what() << endl;
    }

    return 0;
}
