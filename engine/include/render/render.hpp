#ifndef DJANGO_ENGINE_RENDER_RENDER_HPP_
#define DJANGO_ENGINE_RENDER_RENDER_HPP_

#include <nlohmann/json.hpp>
#include <string>

namespace render {
std::string render(const nlohmann::json& j);
}

#endif