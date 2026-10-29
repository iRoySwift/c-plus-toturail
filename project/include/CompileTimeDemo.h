#include <iostream>

namespace Library
{
    inline namespace v1
    {
        void legacyFunction()
        {
            std::cout << "v1" << std::endl;
        };
    }

    inline namespace v2
    {
        void currentFunction()
        {
            std::cout << "v2" << std::endl;
        };
    }
};

class CompileTimeDemo
{
public:
    void demonstrateNamespace()
    {
        Library::v1::legacyFunction();
        Library::v2::currentFunction();
    };
    void demonstrateStaticAssert()
    {
        static_assert(sizeof(int) >= 4, "int >= 32 bits");
    };
};

int test_compile()
{
    CompileTimeDemo demo;
    // 测试命名空间
    demo.demonstrateNamespace();
    // 测试静态断言
    demo.demonstrateStaticAssert();
    return 0;
}
