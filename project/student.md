题目1：智能指针与类设计（基础）
设计一个简单的学生管理系统，要求：
1. 使用 Student 类，包含姓名、年龄、学号
2. 使用 std::unique_ptr 管理学生对象
3. 实现深拷贝构造函数和移动构造函数
4. 使用异常处理输入验证
代码框架：
```c
#include <iostream>
#include <memory>
#include <vector>
#include <string>

// 在这里实现 Student 类

class StudentManager {
private:
    std::vector<std::unique_ptr<Student>> students;
public:
    // 添加学生
    void addStudent(std::unique_ptr<Student> student);

    // 根据学号查找学生
    Student* findStudent(const std::string& id) const;

    // 显示所有学生信息
    void displayAll() const;
};

int main() {
    StudentManager manager;

    // 测试代码
    try {
        auto student1 = std::make_unique<Student>("张三", 20, "2024001");
        manager.addStudent(std::move(student1));

        manager.displayAll();

        // 测试查找功能
        if (auto found = manager.findStudent("2024001")) {
            std::cout << "找到学生: " << found->getName() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    return 0;
}
```

题目2：模板函数与异常安全（中等）

实现一个安全的数组容器类，要求：
5. 使用模板支持任意类型
6. 实现边界检查，越界时抛出异常
7. 使用移动语义优化性能
8. 提供迭代器功能
代码框架：
```c
#include <iostream>
#include <stdexcept>

template<typename T>
class SafeArray {
private:
    T* data;
    size_t size;
public:
    // 构造函数、析构函数、拷贝控制成员

    // 重载[]运算符，进行边界检查

    // 实现begin()和end()方法

    // 实现移动构造函数和移动赋值运算符
};

// 测试函数
void testSafeArray() {
    try {
        SafeArray<int> arr(5);
        for (size_t i = 0; i < 5; ++i) {
            arr[i] = static_cast<int>(i * 10);
        }

        // 测试越界访问
        // arr[10] = 100; // 应该抛出异常

        // 测试迭代器
        for (const auto& elem : arr) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

    } catch (const std::out_of_range& e) {
        std::cerr << "数组越界: " << e.what() << std::endl;
    }
}
```

题目3：继承与多态（综合）
设计一个图形系统，包含不同的图形类，要求：
9. 基类 Shape 包含纯虚函数 area() 和 draw()
10. 派生类 Circle, Rectangle, Triangle
11. 使用 final 关键字防止进一步继承
12. 使用运行时类型识别
代码框架：
```c
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>

class Shape {
protected:
    std::string name;
public:
    Shape(const std::string& n) : name(n) {}
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual void draw() const = 0;

    virtual std::string getName() const final { return name; }
};

// 实现 Circle, Rectangle, Triangle 类

class ShapeManager {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
public:
    void addShape(std::unique_ptr<Shape> shape);

    double totalArea() const;

    void drawAll() const;

    // 使用 RTTI 统计各类图形数量
    void printStatistics() const;
};

int main() {
    ShapeManager manager;

    manager.addShape(std::make_unique<Circle>("圆1", 5.0));
    manager.addShape(std::make_unique<Rectangle>("矩形1", 4.0, 6.0));
    manager.addShape(std::make_unique<Triangle>("三角形1", 3.0, 4.0, 5.0));

    std::cout << "总面积: " << manager.totalArea() << std::endl;
    manager.drawAll();
    manager.printStatistics();

    return 0;
}
```

题目4：Lambda表达式与STL算法（应用）
实现一个数据处理管道，使用现代C++特性：
代码框架：
```c
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

class DataProcessor {
private:
    std::vector<int> data;
public:
    DataProcessor(std::vector<int>&& input) : data(std::move(input)) {}

    // 使用 Lambda 实现各种数据处理操作
    DataProcessor& filter(std::function<bool(int)> predicate);

    DataProcessor& transform(std::function<int(int)> mapper);

    DataProcessor& sort(bool ascending = true);

    // 使用结构化绑定输出统计信息
    void printStatistics() const;

    const std::vector<int>& getData() const { return data; }
};

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    DataProcessor processor(std::move(numbers));

    processor.filter([](int x) { return x % 2 == 0; })  // 过滤偶数
            .transform([](int x) { return x * x; })     // 平方
            .sort(true);                                // 升序排序

    processor.printStatistics();

    std::cout << "处理后的数据: ";
    for (int num : processor.getData()) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
