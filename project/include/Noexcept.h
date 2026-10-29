#pragma once
#include <iostream>
#include <stdexcept>

#include <iostream>
#include <stdexcept>

class ExceptionDemo
{
public:
    void basicExceptionHandling()
    {
        throw std::runtime_error("error");
    };
    void demonstrateNoexcept() noexcept
    {
        try
        {
            // 逻辑错误异常
            throw std::logic_error("逻辑错误");
        }
        catch (const std::logic_error &e)
        {
            std::cout << "逻辑错误: " << e.what() << std::endl;
        }

        try
        {
            // 运行时错误异常
            throw std::runtime_error("运行时错误");
        }
        catch (const std::runtime_error &e)
        {
            std::cout << "运行时错误: " << e.what() << std::endl;
        }

        try
        {
            // 系统错误
            throw std::system_error(EDOM, std::generic_category(), "数学域错误");
        }
        catch (const std::system_error &e)
        {
            std::cout << "系统错误: " << e.what() << ", 错误码: " << e.code() << std::endl;
        }
        std::cout << "程序继续执行..." << std::endl;
    };
};

int test_exception()
{
    ExceptionDemo demo;
    // 测试异常处理
    std::cout << std::boolalpha;
    std::cout << "may_throw is noexcept: " << noexcept(demo.basicExceptionHandling()) << std::endl; // false
    std::cout << "no_throw is noexcept: " << noexcept(demo.demonstrateNoexcept()) << std::endl;     // true
    // 测试noexcept运算符
    demo.demonstrateNoexcept();
    return 0;
}
