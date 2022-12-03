#ifndef DJANGO_ENGINE_MODULE_HPP_
#define DJANGO_ENGINE_MODULE_HPP_

#include <nlohmann/json.hpp>

#include <memory>
#include <optional>
#include <string>

namespace Django {
class Module {

   public:
    Module();
    ~Module();
    Module(Module&&) = default;
    Module& operator=(Module&&) = default;

    Module(const std::string& filepath);

    std::string to_string() const noexcept;
    // Not support any type yet
    void set(const std::string& key, const nlohmann::json& value);
    void set(const std::string& key, nlohmann::json&& value);
    std::optional<nlohmann::json> get(const std::string& key) const noexcept;

    const std::string render() const;

   private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};
}  // namespace Django

#endif