#include <algorithm>
#include <ranges>
#include <render/custom_filter.hpp>
#include <stdexcept>
#include <vector>

namespace detail {
std::vector<std::string> split_var(const std::string& var_tok);
};

std::string render::value_lookup(const std::string& var_tok, const json& j) {
    // Split by dot operator
    const auto& splitted_tok = detail::split_var(var_tok);

    json j_copy = j;
    for (const auto& name : splitted_tok) {
        if (j_copy.contains(name))
            j_copy = j_copy[name];
        else
            throw std::range_error("Could not find" + var_tok + " in " + j.dump());
    }

    std::string ret;
    // TODO: dynamic casting type
    j_copy.get_to<std::string>(ret);

    return ret;
}

std::string render::custom_filter::empty_callback([[maybe_unused]] const std::string& var_tok,
                                                  [[maybe_unused]] const json& j) {
    return "";
}

std::string render::custom_filter::default_value_callback(const std::string& value, const std::string& var_tok,
                                                          const json& j) {

    try {
        return render::value_lookup(var_tok, j);
    } catch (...) {
        return value;
    }
}

std::string render::custom_filter::size_callback(const std::string& var_tok, const json& j) {
    const auto& val = render::value_lookup(var_tok, j).size();
    return std::to_string(val);
}

std::string render::custom_filter::length_callback(const std::string& var_tok, const json& j) {
    const auto& val = render::value_lookup(var_tok, j).length();
    return std::to_string(val);
}

std::string render::custom_filter::lower_callback(const std::string& var_tok, const json& j) {
    const auto& val = render::value_lookup(var_tok, j);
    std::string res;
    std::transform(val.begin(), val.end(), res.begin(), [](const char& c) { return std::tolower(c); });
    return res;
}

std::string render::custom_filter::upper_callback(const std::string& var_tok, const json& j) {
    const auto& val = render::value_lookup(var_tok, j);
    std::string res;
    std::transform(val.begin(), val.end(), res.begin(), [](const char& c) { return std::toupper(c); });
    return res;
}

std::vector<std::string> detail::split_var(const std::string& var_tok) {
    std::vector<std::string> ret;
    for (const auto& tok : var_tok | std::ranges::views::split('.'))
        ret.emplace_back(std::string(tok.begin(), tok.end()));

    return ret;
}