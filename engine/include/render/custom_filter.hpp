#ifndef DJANGO_ENGINE_RENDER_CUSTOM_FILTER_HPP_
#define DJANGO_ENGINE_RENDER_CUSTOM_FILTER_HPP_

#include <functional>
#include <nlohmann/json.hpp>
#include <string>

namespace render {
using json = nlohmann::json;
using filter_callback = std::function<std::string(const std::string& var_tok, const json& j)>;

std::string value_lookup(const std::string& var_tok, const json& j);

namespace custom_filter {

std::string empty_callback(const std::string& var_tok, const json& j);
std::string default_value_callback(const std::string& value, const std::string& var_tok, const json& j);
std::string size_callback(const std::string& var_tok, const json& j);
std::string length_callback(const std::string& var_tok, const json& j);
std::string lower_callback(const std::string& var_tok, const json& j);
std::string upper_callback(const std::string& var_tok, const json& j);

}  // namespace custom_filter
}  // namespace render

#endif