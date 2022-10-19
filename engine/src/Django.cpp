#include <Django.hpp>

Django::Module Django::parse(const std::string &filepath)
{
    return Django::Module(filepath);
}
