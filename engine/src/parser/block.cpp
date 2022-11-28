#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <parser/block.hpp>
#include <string_view>
#include <tuple>
#include <utility>

using json = nlohmann::json;

namespace detail {

namespace macro {
constexpr auto BLOCK_OPEN = "{% block ([^ \n]+) %}";
constexpr auto BLOCK_CLOSE = "{% endblock %}";
constexpr auto BLOCK_EXPR = "{% block ([^ \n]+) %}|{% endblock %}";
}  // namespace macro

const boost::regex block_expr{macro::BLOCK_EXPR};
const boost::regex block_open{macro::BLOCK_OPEN};
const boost::regex block_close{macro::BLOCK_CLOSE};

json proc_block_impl(const std::string& to_be_proc);
}  // namespace detail

std::string parser::proc_block(const std::string& extended_ctx) {
    // Recursively find all blocks
    const auto& hierarchy_blocks = detail::proc_block_impl(extended_ctx);

    // Combine all blocks
    ;
}

json detail::proc_block_impl(const std::string& ctx) {
    json result;

    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;
    auto start = ctx.begin();
    while (boost::regex_search(start, ctx.end(), what, block_expr, flags)) {
        json block_info;

        if (what[0] == macro::BLOCK_CLOSE) {
            // is close
        } else {
            // is open
        }

        block_info["name"] = what[1].str();  // block name
        block_info["prefix"] = std::string(start, what[0].first);
        block_info["body"] = proc_block_impl(what[2].str());
        block_info["postfix"] = "";

        result.emplace_back(block_info);

        // update search position:
        start = what[0].second;
        // update flags:
        flags |= boost::match_prev_avail;
        flags |= boost::match_not_bob;
    }

    // Append tailing ctx
    result["postfix"] = std::string(start, ctx.end());

    return result;
}