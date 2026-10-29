#include <iostream>
#include <typeinfo>

class Base
{
public:
    virtual ~Base() = default;
    virtual void identify() const
    {
        std::cout << "I am Base" << std::endl;
    };
};

class Derived : public Base
{
public:
    void identify() const override
    {
        std::cout << "I am Derived" << std::endl;
    };
};

class TypeConversionDemo
{
public:
    void demonstrateCasts()
    {
        Base *b = new Derived();
        // 使用 dynamic_cast 进行安全的向下转换
        Derived *d = dynamic_cast<Derived *>(b);
        d->identify();
        std::cout << std::endl;
    };

    template <typename T>
    void demonstrateTypeid()
    {
        Base *b = new Derived();
        std::cout << typeid(T).name() << std::endl;
    };
};

int test_type_conversion()
{
    TypeConversionDemo demo;
    // 测试类型转换
    demo.demonstrateCasts();
    // 测试RTTI
    demo.demonstrateTypeid<int>();
    demo.demonstrateTypeid<const double &>();
    return 0;
}
