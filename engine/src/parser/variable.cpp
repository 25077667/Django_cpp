#include <boost/regex.hpp>
#include <parser/variable.hpp>

#include <unordered_map>

using nlohmann::json;

namespace detail {
std::unordered_map<std::string, std::string> find_variable_impl(const std::string& str);
};

nlohmann::json parser::find_variables(const std::string& str) {
    json j;

    // No sub-members
    for (const auto& [key, value] : detail::find_variable_impl(str))
        j[key] = value;

    return j;
}

std::unordered_map<std::string, std::string> detail::find_variable_impl(const std::string& str) {
    const boost::regex expr{"{{ (\\w+) }}"};
    std::unordered_map<std::string, std::string> table;
    boost::sregex_iterator m1(str.begin(), str.end(), expr);
    boost::sregex_iterator m2;
    std::for_each(m1, m2, [&table](const boost::match_results<std::string::const_iterator>& what) {
        ;  // For formatting blank line
        table[what[1].str()] = "";
    });

    return table;
}