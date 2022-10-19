#include <Django.hpp>
#include <iostream>

int main()
{
    const auto nothing = Django::parse("../template/sample.html");
    std::cout << nothing.to_string() << std::endl;

    return 0;
}