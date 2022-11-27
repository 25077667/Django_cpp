#include <render/render.hpp>
#include <render/tags.hpp>
#include <render/variable.hpp>

using json = nlohmann::json;

namespace detail {
std::string get_origin_ctx(const json& j);
}  // namespace detail

std::string render::render(const json& j) {
    const auto& origin_ctx = detail::get_origin_ctx(j["context"]);
    // TODO: Rendering {% block %}
    // TODO: Rendering tags (for loop and if condition)

    // Rendering variables w/wo filters
    // TODO: Support multiple filters
    const auto& ret = render::variable(origin_ctx, j["variable"]);

    return ret;
}

std::string detail::get_origin_ctx(const json& j) {
    std::string ret;
    j.get_to<std::string>(ret);
    return ret;
}