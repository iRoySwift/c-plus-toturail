#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Student 类和 StudentManager 的实现
struct Student
{
private:
    string name;
    int age;
    string id;

public:
    Student(const string &name, int age, const string &id) : name(name), age(age), id(id) {};
    string getName() { return name; }
    int getAge() const { return age; }
    string getId() const { return id; }

    void display() const
    {
        cout << "姓名: " << name << ", 年龄: " << age << ", 学号: " << id << endl;
    }
};

class StudentManager
{
private:
    vector<unique_ptr<Student>> students;

public:
    // 添加学生
    void addStudent(unique_ptr<Student> student);

    // 根据学号查找学生
    Student *findStudent(const string &id) const;

    // 显示所有学生信息
    void displayAll() const;
};

#endif // STUDENT_H
