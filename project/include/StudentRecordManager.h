#pragma once;
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
using namespace std;

struct StudentRecord
{
    int id;
    char name[50];
    double score;
};

class StudentManager
{
private:
    std::string filename;

public:
    StudentManager(const std::string &fname) : filename(fname)
    {
        // 构造时清空文件，或者你可以提供一个专门的 clear() 方法
        std::ofstream out(filename, std::ios::trunc);
        out.close();
    }
    void addStudent(const StudentRecord &student)
    {
        std::ofstream out(filename, std::ios::app);
        if (!out.is_open())
        {
            cerr << "打开文件失败" << endl;
        }
        out << student.id << " "
            << student.name << " "
            << student.score << " ";
        out << endl;
        out.close();
    }
    std::vector<std::unique_ptr<StudentRecord>> readAllStudents()
    {
        vector<std::unique_ptr<StudentRecord>> students;
        ifstream in(filename);
        if (!in.is_open())
        {
            cerr << "打开文件失败" << endl;
            return students;
        }

        while (true)
        {
            auto student = make_unique<StudentRecord>();
            // 尝试读取
            in >> student->id >> student->name >> student->score;

            // 检查是否读取成功
            if (in.fail())
                break;

            students.push_back(move(student));
        }
        in.close();
        return students;
    }
    StudentRecord *findStudentById(int id)
    {
        vector<std::unique_ptr<StudentRecord>> students = readAllStudents();
        for (auto &student : students)
        {
            if (student->id == id)
            {
                return student.release();
            }
        }
        return nullptr;
    };
    bool updateStudentScore(int id, double newScore)
    {
        vector<std::unique_ptr<StudentRecord>> students = readAllStudents();
        bool found = false;
        for (auto &student : students)
        {
            if (student->id == id)
            {
                student->score = newScore;
                found = true;

                break;
            }
        }
        if (!found)
            return false;
        std::ofstream out(filename);
        if (!out.is_open())
            return false;
        for (const auto &student : students)
        {
            cout << student->score << endl;
            out << student->id << " "
                << student->name << " "
                << student->score << " ";
            out << endl;
        }
        out.close();
        return found;
    }
    void displayAllStudents()
    {
        vector<std::unique_ptr<StudentRecord>> students = readAllStudents();
        for (const auto &student : students)
        {
            cout << "ID: " << student->id << ", Name: " << student->name << ", Score: " << student->score << endl;
        }
    }
};

int test_student_record_manage()
{
    StudentManager manager("students.dat");

    // 测试代码
    StudentRecord s1 = {1001, "张三", 85.5};
    StudentRecord s2 = {1002, "李四", 92.0};

    manager.addStudent(s1);
    manager.addStudent(s2);

    manager.displayAllStudents();

    // 测试查找和更新功能
    StudentRecord *student = manager.findStudentById(1002);
    cout << "查找到的学生是： " << student->name << "分数是： " << student->score << endl;
    delete student;

    bool flag = manager.updateStudentScore(1001, 85);
    if (flag)
    {
        cout << "更新成功" << endl;
        manager.displayAllStudents();
    }
}
