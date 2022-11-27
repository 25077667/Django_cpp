#ifndef DJANGO_ENGINE_RENDER_TAGS_HPP_
#define DJANGO_ENGINE_RENDER_TAGS_HPP_
#include <string>

namespace render {
namespace tags {
std::string if_statement(const std::string& ctx);
std::string for_loop_statement(const std::string& ctx);
}  // namespace tags

std::string extend_tags(const std::string& ctx);

}  // namespace render

#endif