#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

class ProductManager
{
private:
    struct Product
    {
        std::string name;
        double price;
        int stock;
    };
    std::vector<Product> products;

public:
    void addProduct(const std::string &name, double price, int stock)
    {
        products.push_back({name, price, stock});
    }
    void writeToFile(const std::string &filename)
    {
        std::ofstream out(filename);
        for (const auto &product : products)
        {
            out << std::setw(20) << std::left << product.name
                << std::setprecision(2) << std::right << product.price
                << std::setw(10) << std::right << product.stock
                << std::endl;
        }
        out.close();
    }
    void readFromFile(const std::string &filename)
    {
        std::ifstream in(filename);
        // 检查文件是否成功打开
        if (!in.is_open())
        {
            std::cerr << "错误：无法打开文件 " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(in, line))
        {
            std::cout << line << std::endl;
        }
        in.close();
    }
    void displayProducts() const
    {
        for (const auto &product : products)
        {
            std::cout << std::setw(20) << std::left << product.name
                      << std::setprecision(2) << std::right << product.price
                      << std::setw(10) << std::right << product.stock
                      << std::endl;
        }
    }
};

int test_product_manager()
{
    ProductManager manager;

    // 测试代码
    manager.addProduct("苹果", 5.50, 100);
    manager.addProduct("香蕉", 3.20, 150);
    manager.addProduct("橙子", 4.80, 80);

    manager.writeToFile("products.txt");
    manager.readFromFile("products1.txt");
    manager.displayProducts();

    return 0;
}
