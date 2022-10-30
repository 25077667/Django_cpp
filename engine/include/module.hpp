#ifndef DJANGO_ENGINE_MODULE_HPP_
#define DJANGO_ENGINE_MODULE_HPP_

#include <memory>
#include <optional>
#include <string>

namespace Django {
class Module {

   public:
    Module();
    ~Module();
    Module(const Module&) = default;
    Module(Module&&) = default;
    Module& operator=(const Module&) = default;
    Module& operator=(Module&&) = default;

    Module(const std::string& filepath);

    std::string to_string() const noexcept;
    // Not support any type yet
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const noexcept;

   private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};
}  // namespace Django

#endif