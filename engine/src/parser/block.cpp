#include <boost/regex.hpp>
#include <nlohmann/json.hpp>
#include <parser/block.hpp>
#include <tuple>

using json = nlohmann::json;

namespace detail {
constexpr auto block_open = "{% block ([^ ])+ %}";
constexpr auto block_close = "{% endblock %}";
constexpr auto block_ctx = "(.*)";

std::tuple<const std::string, const json, const std::string> proc_block_impl(const std::string& to_be_proc);
}  // namespace detail

std::string parser::proc_block(const std::string& extended_ctx) {
    // Recursively find all blocks
    const auto& [before_blocks, blocks, after_blocks] = detail::proc_block_impl(extended_ctx);

    // Combine all blocks
    ;
}
