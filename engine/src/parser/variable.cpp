#include <boost/regex.hpp>
#include <iostream>
#include <optional>
#include <parser/variable.hpp>
#include <ranges>
#include <vector>

using nlohmann::json;

namespace detail {
std::vector<std::string> find_variable_impl(const std::string& str);
std::optional<std::string> valid_variable_token(const std::string& str);
json transform_nested_variable(const std::string& var_str);
};  // namespace detail

nlohmann::json parser::find_variables(const std::string& str) {
    json j;

    for (const auto& tok : detail::find_variable_impl(str)) {
        const auto& to_be_inserted = detail::transform_nested_variable(tok);
        // TODO: Improve performance here
        // Don't insert duplicated keys
        if (j.dump().find(to_be_inserted.dump()) == std::string::npos)  // Not already exist
            for (const auto& [key, value] : to_be_inserted.items())
                j[key] = value;
    }

    return j;
}

std::vector<std::string> detail::find_variable_impl(const std::string& str) {
    const boost::regex expr{
        "{{ ([^ ]+) }}"               // Single variable
        "|{% for \\w+ in ([^ ]+) %}"  // Variable in a for loop
    };

    std::vector<std::string> table;
    boost::sregex_iterator m1(str.begin(), str.end(), expr);
    boost::sregex_iterator m2;
    std::for_each(m1, m2, [&table](const boost::match_results<std::string::const_iterator>& what) {
        for (size_t i = 1; i < what.size(); ++i) {
            if (what[i].str().size() == 0)
                continue;

            const auto tok = valid_variable_token(what[i].str());
            if (tok.has_value())
                table.push_back(tok.value());
        }
    });

    return table;
}

std::optional<std::string> detail::valid_variable_token(const std::string& str) {
    const boost::regex expr{
        "([a-zA-Z_]\\w*(\\.[a-zA-Z_]\\w*)*).*"  // (Single variable).*
    };

    boost::smatch what;
    if (boost::regex_match(str, what, expr) && what[1].str().size()) {
        return what[1].str();
    } else
        return std::nullopt;
}

json detail::transform_nested_variable(const std::string& var_str) {
    auto count_members = [](const std::string& str) -> int {
        int counter = 1;
        for ([[maybe_unused]] const auto& _ : str | std::ranges::views::filter([](char c) { return c == '.'; }))
            ++counter;
        return counter;
    };

    json j;
    if (count_members(var_str) == 1) {
        j[var_str] = "";
    } else {
        const auto split_point = var_str.find_first_of('.');
        j[var_str.substr(0, split_point)] = transform_nested_variable(var_str.substr(split_point + 1));
    }

    return j;
}