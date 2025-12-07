#include <iostream>
#include <optional>
#include <variant>
#include <string_view>
#include <filesystem>
#include <vector>
using namespace std;

class Cpp17FeaturesDemo
{
public:
    void optionalDemo()
    {
        std::optional<bool> mayBe;
        if (!mayBe.has_value())
        {
            cout << "optional mayBe: 没有数据" << endl;
        }
    };
    void variantDemo()
    {
        std::variant<string, bool, int> v = 1;
        // 错误原因：std::cout 不知道如何直接打印 variant，因为它不知道当前里面存的是什么类型。
        // 解决方法：使用 std::visit 配合 lambda 表达式来访问当前的值。
        std::visit([](auto &&arg)
                   { cout << "variant 的值为: " << arg << endl; }, v);

        v = "x";
        std::visit([](auto &&arg)
                   { cout << "variant 的值为: " << arg << endl; }, v);
    };
    void stringViewDemo()
    {
        std::string_view str = "test";
        cout << "string_view str 值" << str << endl;
    };
    void filesystemDemo()
    {
        namespace fs = std::filesystem;
        if (!fs::exists("test.txt"))
        {
            cout << "文件不存在" << endl;
        }
    };
};

class Configuration
{
private:
    std::optional<int> port;
    std::variant<std::string, int> id;

public:
    void setPort(std::optional<int> p)
    {
        port = p;
    };
    void setId(std::variant<std::string, int> newId)
    {
        id = newId;
    };
    void display() const
    {
        if (port.has_value())
        {
            cout << "端口为: " << port.value() << endl;
        }

        std::visit([](auto &&v)
                   {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T,string>) {
                    cout << "ID 为: string" << endl;
                } else {
                    cout << "ID 为: int" << endl;
                } }, id);
    };
};

int test_cpp17_features()
{
    Cpp17FeaturesDemo demo;
    Configuration config;

    // 测试各种C++17特性
    demo.optionalDemo();
    demo.variantDemo();
    demo.stringViewDemo();
    demo.filesystemDemo();

    // 配置类测试
    config.setPort(8080);
    config.setId("server01");
    config.display();

    return 0;
}
