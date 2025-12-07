题目1：智能指针与类设计（基础）
```c
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

class Student {
private:
    std::string name;
    int age;
    std::string id;
public:
    Student(const std::string& n, int a, const std::string& i) : name(n), age(a), id(i) {
        if (a < 0 || a > 150) {
            throw std::invalid_argument("年龄必须在0-150之间");
        }
        if (i.empty()) {
            throw std::invalid_argument("学号不能为空");
        }
    }

    // 深拷贝构造函数
    Student(const Student& other) : name(other.name), age(other.age), id(other.id) {}

    // 移动构造函数
    Student(Student&& other) noexcept : name(std::move(other.name)), age(other.age), id(std::move(other.id)) {}

    // 拷贝赋值运算符
    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            id = other.id;
        }
        return *this;
    }

    // 移动赋值运算符
    Student& operator=(Student&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            age = other.age;
            id = std::move(other.id);
        }
        return *this;
    }

    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getId() const { return id; }

    void display() const {
        std::cout << "姓名: " << name << ", 年龄: " << age << ", 学号: " << id << std::endl;
    }
};

class StudentManager {
private:
    std::vector<std::unique_ptr<Student>> students;
public:
    void addStudent(std::unique_ptr<Student> student) {
        students.push_back(std::move(student));
    }

    Student* findStudent(const std::string& id) const {
        for (const auto& student : students) {
            if (student->getId() == id) {
                return student.get();
            }
        }
        return nullptr;
    }

    void displayAll() const {
        if (students.empty()) {
            std::cout << "没有学生信息。" << std::endl;
            return;
        }
        for (const auto& student : students) {
            student->display();
        }
    }
};

int main() {
    StudentManager manager;

    try {
        auto student1 = std::make_unique<Student>("张三", 20, "2024001");
        manager.addStudent(std::move(student1));

        auto student2 = std::make_unique<Student>("李四", 22, "2024002");
        manager.addStudent(std::move(student2));

        manager.displayAll();

        if (auto found = manager.findStudent("2024001")) {
            std::cout << "找到学生: " << found->getName() << std::endl;
        }

        // 测试查找不存在的学生
        if (auto found = manager.findStudent("999999")) {
            std::cout << "找到学生: " << found->getName() << std::endl;
        } else {
            std::cout << "未找到学号为999999的学生" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    return 0;
}
```

题目2：模板函数与异常安全（中等）
```c
#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class SafeArray {
private:
    T* data;
    size_t size;
public:
    // 构造函数
    explicit SafeArray(size_t s) : size(s) {
        data = new T[size]();
    }

    // 拷贝构造函数
    SafeArray(const SafeArray& other) : size(other.size) {
        data = new T[size];
        std::copy(other.data, other.data + size, data);
    }

    // 移动构造函数
    SafeArray(SafeArray&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // 拷贝赋值运算符
    SafeArray& operator=(const SafeArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    // 移动赋值运算符
    SafeArray& operator=(SafeArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // 析构函数
    ~SafeArray() {
        delete[] data;
    }

    // 重载[]运算符，进行边界检查
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("索引 " + std::to_string(index) + " 超出范围 [0, " + std::to_string(size - 1) + "]");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("索引 " + std::to_string(index) + " 超出范围 [0, " + std::to_string(size - 1) + "]");
        }
        return data[index];
    }

    // 实现begin()和end()方法
    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + size; }
    const T* end() const { return data + size; }

    size_t getSize() const { return size; }
};

void testSafeArray() {
    try {
        SafeArray<int> arr(5);
        for (size_t i = 0; i < 5; ++i) {
            arr[i] = static_cast<int>(i * 10);
        }

        // 测试迭代器
        std::cout << "数组元素: ";
        for (const auto& elem : arr) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        // 测试拷贝构造
        SafeArray<int> arr2 = arr;
        std::cout << "拷贝后的数组: ";
        for (const auto& elem : arr2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        // 测试移动构造
        SafeArray<int> arr3 = std::move(arr2);
        std::cout << "移动后的数组: ";
        for (const auto& elem : arr3) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        // 测试越界访问（取消注释会抛出异常）
        // arr[10] = 100; // 应该抛出异常

    } catch (const std::out_of_range& e) {
        std::cerr << "数组越界: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "其他错误: " << e.what() << std::endl;
    }
}

int main() {
    testSafeArray();
    return 0;
}
```
题目3：继承与多态（综合）
```c
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <cmath>
#include <map>

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

class Circle final : public Shape {
private:
    double radius;
public:
    Circle(const std::string& n, double r) : Shape(n), radius(r) {
        if (r <= 0) {
            throw std::invalid_argument("半径必须大于0");
        }
    }

    double area() const override {
        return M_PI * radius * radius;
    }

    void draw() const override {
        std::cout << "绘制圆形 [" << name << "]: 半径 = " << radius
                  << ", 面积 = " << area() << std::endl;
    }

    double getRadius() const { return radius; }
};

class Rectangle final : public Shape {
private:
    double width, height;
public:
    Rectangle(const std::string& n, double w, double h) : Shape(n), width(w), height(h) {
        if (w <= 0 || h <= 0) {
            throw std::invalid_argument("宽度和高度必须大于0");
        }
    }

    double area() const override {
        return width * height;
    }

    void draw() const override {
        std::cout << "绘制矩形 [" << name << "]: " << width << " x " << height
                  << ", 面积 = " << area() << std::endl;
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

class Triangle final : public Shape {
private:
    double side1, side2, side3;
public:
    Triangle(const std::string& n, double s1, double s2, double s3)
        : Shape(n), side1(s1), side2(s2), side3(s3) {
        if (s1 <= 0 || s2 <= 0 || s3 <= 0) {
            throw std::invalid_argument("边长必须大于0");
        }
        // 检查三角形不等式
        if (s1 + s2 <= s3 || s1 + s3 <= s2 || s2 + s3 <= s1) {
            throw std::invalid_argument("边长不满足三角形条件");
        }
    }

    double area() const override {
        // 海伦公式
        double s = (side1 + side2 + side3) / 2;
        return std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    void draw() const override {
        std::cout << "绘制三角形 [" << name << "]: 边长 = " << side1
                  << ", " << side2 << ", " << side3 << ", 面积 = " << area() << std::endl;
    }

    double getSide1() const { return side1; }
    double getSide2() const { return side2; }
    double getSide3() const { return side3; }
};

class ShapeManager {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
public:
    void addShape(std::unique_ptr<Shape> shape) {
        shapes.push_back(std::move(shape));
    }

    double totalArea() const {
        double total = 0.0;
        for (const auto& shape : shapes) {
            total += shape->area();
        }
        return total;
    }

    void drawAll() const {
        std::cout << "=== 绘制所有图形 ===" << std::endl;
        for (const auto& shape : shapes) {
            shape->draw();
        }
        std::cout << "===================" << std::endl;
    }

    // 使用 RTTI 统计各类图形数量
    void printStatistics() const {
        std::map<std::string, int> typeCount;

        for (const auto& shape : shapes) {
            const std::type_info& type = typeid(*shape);

            if (type == typeid(Circle)) {
                typeCount["圆形"]++;
            } else if (type == typeid(Rectangle)) {
                typeCount["矩形"]++;
            } else if (type == typeid(Triangle)) {
                typeCount["三角形"]++;
            } else {
                typeCount["未知类型"]++;
            }
        }

        std::cout << "=== 图形统计 ===" << std::endl;
        for (const auto& [type, count] : typeCount) {
            std::cout << type << ": " << count << " 个" << std::endl;
        }
        std::cout << "总计: " << shapes.size() << " 个图形" << std::endl;
        std::cout << "总面积: " << totalArea() << std::endl;
    }
};

int main() {
    ShapeManager manager;

    try {
        manager.addShape(std::make_unique<Circle>("圆1", 5.0));
        manager.addShape(std::make_unique<Rectangle>("矩形1", 4.0, 6.0));
        manager.addShape(std::make_unique<Triangle>("三角形1", 3.0, 4.0, 5.0));
        manager.addShape(std::make_unique<Circle>("圆2", 3.0));
        manager.addShape(std::make_unique<Rectangle>("矩形2", 2.0, 8.0));

        manager.drawAll();
        manager.printStatistics();

    } catch (const std::exception& e) {
        std::cerr << "创建图形时出错: " << e.what() << std::endl;
    }

    return 0;
}
```
题目4：Lambda表达式与STL算法（应用）
```c
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <tuple>

class DataProcessor {
private:
    std::vector<int> data;
public:
    DataProcessor(std::vector<int>&& input) : data(std::move(input)) {}

    // 使用 Lambda 实现过滤操作
    DataProcessor& filter(std::function<bool(int)> predicate) {
        std::vector<int> result;
        std::copy_if(data.begin(), data.end(), std::back_inserter(result), predicate);
        data = std::move(result);
        return *this;
    }

    // 使用 Lambda 实现转换操作
    DataProcessor& transform(std::function<int(int)> mapper) {
        std::transform(data.begin(), data.end(), data.begin(), mapper);
        return *this;
    }

    // 排序操作
    DataProcessor& sort(bool ascending = true) {
        if (ascending) {
            std::sort(data.begin(), data.end());
        } else {
            std::sort(data.begin(), data.end(), std::greater<int>());
        }
        return *this;
    }

    // 使用结构化绑定输出统计信息
    void printStatistics() const {
        if (data.empty()) {
            std::cout << "数据为空" << std::endl;
            return;
        }

        auto [min, max] = std::minmax_element(data.begin(), data.end());
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double mean = sum / data.size();

        // 计算中位数
        double median = 0.0;
        std::vector<int> sorted = data;
        std::sort(sorted.begin(), sorted.end());
        if (sorted.size() % 2 == 0) {
            median = (sorted[sorted.size()/2 - 1] + sorted[sorted.size()/2]) / 2.0;
        } else {
            median = sorted[sorted.size()/2];
        }

        // 使用结构化绑定
        auto [min_val, max_val, mean_val, median_val] =
            std::make_tuple(*min, *max, mean, median);

        std::cout << "=== 数据统计 ===" << std::endl;
        std::cout << "数据量: " << data.size() << std::endl;
        std::cout << "最小值: " << min_val << std::endl;
        std::cout << "最大值: " << max_val << std::endl;
        std::cout << "平均值: " << mean_val << std::endl;
        std::cout << "中位数: " << median_val << std::endl;
        std::cout << "总和: " << sum << std::endl;
    }

    const std::vector<int>& getData() const { return data; }

    // 显示数据
    void displayData(const std::string& title = "数据") const {
        std::cout << title << ": ";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i < data.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10};

    std::cout << "原始数据: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;

    DataProcessor processor(std::move(numbers));

    // 链式调用：过滤偶数 → 平方 → 升序排序
    processor.filter([](int x) {
            std::cout << "过滤检查: " << x << " -> " << (x % 2 == 0) << std::endl;
            return x % 2 == 0;
        })  // 过滤偶数
        .transform([](int x) {
            int result = x * x;
            std::cout << "转换: " << x << " -> " << result << std::endl;
            return result;
        })     // 平方
        .sort(true);                                // 升序排序

    processor.displayData("处理后的数据");
    processor.printStatistics();

    // 另一个例子：处理奇数
    std::cout << "\n=== 另一个处理流程 ===" << std::endl;
    std::vector<int> moreNumbers = {15, 12, 18, 11, 19, 13, 17, 14, 16};
    DataProcessor processor2(std::move(moreNumbers));

    processor2.filter([](int x) { return x % 2 != 0; })  // 过滤奇数
             .transform([](int x) { return x + 100; })   // 每个数加100
             .sort(false);                               // 降序排序

    processor2.displayData("奇数处理后的数据");
    processor2.printStatistics();

    return 0;
}
```
