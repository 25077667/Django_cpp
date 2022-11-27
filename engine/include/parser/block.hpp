#ifndef DJANGO_ENGINE_PARSER_BLOCK_HPP_
#define DJANGO_ENGINE_PARSER_BLOCK_HPP_

#include <string>

namespace parser {
// Replace all blocks' contents as the last appearing block
std::string proc_block(const std::string& extended_ctx);
}  // namespace parser

#endif