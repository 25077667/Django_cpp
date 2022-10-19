#include <module.hpp>
#include <fstream>
#include <stdexcept>

struct Django::Module::Impl
{
    Impl() = default;
    Impl(const std::string &filepath);

    std::string filepath;
    std::string contents;
};

Django::Module::Impl::Impl(const std::string &filepath_) : filepath{filepath_},
                                                           contents{
                                                               [&filepath_]() -> std::string
                                                               {
                                                                   std::ifstream input_file(filepath_);
                                                                   if (!input_file.is_open())
                                                                       throw std::runtime_error("file could not be opened!\n");

                                                                   return std::string((std::istreambuf_iterator<char>(input_file)),
                                                                                      std::istreambuf_iterator<char>());
                                                               }()}
{
}

Django::Module::Module() : pImpl{std::make_unique<Django::Module::Impl>()}
{
}
Django::Module::~Module() {}

Django::Module::Module(const std::string &filepath) : pImpl{std::make_unique<Django::Module::Impl>(filepath)}
{
}

std::string Django::Module::to_string() const noexcept
{
    return pImpl->contents;
}
