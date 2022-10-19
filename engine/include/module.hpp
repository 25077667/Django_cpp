#ifndef DJANGO_ENGINE_MODULE_HPP_
#define DJANGO_ENGINE_MODULE_HPP_

#include <string>
#include <memory>

namespace Django
{
    class Module
    {

    public:
        Module();
        ~Module();
        Module(const Module &) = default;
        Module(Module &&) = default;
        Module &operator=(const Module &) = default;
        Module &operator=(Module &&) = default;

        Module(const std::string &filepath);

        std::string to_string() const noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
}

#endif