#ifndef DJANGO_ENGINE_RENDER_FILTER_HPP_
#define DJANGO_ENGINE_RENDER_FILTER_HPP_

#include <functional>
#include <nlohmann/json.hpp>
#include <render/custom_filter.hpp>
#include <string>

namespace render {

// Return a function that could process the variable token, which function would
// returns the result after precessing.
filter_callback parse_filter(const std::string& filter_raw_str);
}  // namespace render

#endif