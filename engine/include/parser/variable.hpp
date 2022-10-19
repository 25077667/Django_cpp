#ifndef DJANGO_ENGINE_PARSER_VARIABLE_HPP_
#define DJANGO_ENGINE_PARSER_VARIABLE_HPP_

#include <nlohmann/json.hpp>
#include <string>

namespace parser {
/* Suppose the key-value map is uniuqe */
nlohmann::json find_variables(const std::string& str);
}  // namespace parser

#endif