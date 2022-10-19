#ifndef DJANGO_ENGINE_PARSER_VARIABLE_HPP_
#define DJANGO_ENGINE_PARSER_VARIABLE_HPP_

#include <unordered_map>

namespace parser {
/* Suppose the key-value map is uniuqe */
std::unordered_map<std::string, std::string> find_variables(const std::string& str);
}  // namespace parser

#endif