#ifndef DJANGO_ENGINE_RENDER_VARIABLE_HPP_
#define DJANGO_ENGINE_RENDER_VARIABLE_HPP_

#include <nlohmann/json.hpp>
#include <string>

namespace render {

// Rendering variables w/wo filter
// Suppose there is exactly one variable w/wo a filter
// Suppose the variable in json is a "string"
std::string variable(const std::string& ctx, const nlohmann::json& var_j);
}  // namespace render

#endif