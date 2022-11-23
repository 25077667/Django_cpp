#include <boost/regex.hpp>
#include <render/filter.hpp>
#include <render/variable.hpp>
#include <utility>

using json = nlohmann::json;

namespace detail {
std::pair<std::string, std::string> split_var_filter(const std::string& entire_var_region);

}  // namespace detail

std::string render::variable(const std::string& ctx, const json& j) {
    const boost::regex expr{
        "{{ ([^ ]+) }}"  // Single variable
    };
    // TODO: Supporting white spaces, multiple filters, etc.

    std::string result;

    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    auto start = ctx.begin();
    while (boost::regex_search(start, ctx.end(), what, expr, flags)) {
        const auto& variable_token = what[1].str();

        // Append those stuff before variable's placeholder
        result += std::string(start, what[0].first);

        // Split by operator| for a filter
        const auto& [var_tok, filter] = detail::split_var_filter(what[0].str());
        // TODO: Supporting multiple filters here
        const auto& process_fn = render::parse_filter(filter);
        result += process_fn(var_tok, j);

        // update search position:
        start = what[0].second;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }

    // Append tailing ctx
    result.append(start, ctx.end());

    return result;
}

std::pair<std::string, std::string> detail::split_var_filter(const std::string& entire_var_region) {
    const auto& var_tok = entire_var_region;  // alias

    const auto split_pos = var_tok.find_first_of('|');
    if (split_pos != var_tok.npos)
        return std::make_pair(std::string(var_tok.begin(), var_tok.begin() + split_pos),
                              std::string(var_tok.begin() + split_pos + 1, var_tok.end()));
    else
        return std::make_pair(var_tok, std::string());
}
