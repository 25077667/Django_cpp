#include <render/filter.hpp>
#include <string_view>
#include <vector>

using json = nlohmann::json;

namespace detail {
static constexpr auto para_delia = ':';

auto split_ctrl_tok_para(const std::string& filter_raw_str) -> std::tuple<std::string, std::string>;

namespace literal {
// https://learnmoderncpp.com/2020/06/01/strings-as-switch-case-labels/
constexpr unsigned long hash_djb2a(const std::string_view sv) {
    unsigned long hash{5381};
    for (unsigned char c : sv) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

constexpr unsigned long operator"" _sh(const char* str, size_t len) {
    return hash_djb2a(std::string_view{str, len});
}
}  // namespace literal
}  // namespace detail

render::filter_callback render::parse_filter(const std::string& filter_raw_str) {
    // @filter_raw_str format:
    // default:"nothing"
    // length
    // lower
    // size

    render::filter_callback process_fn = render::custom_filter::empty_callback;

    // NOP
    if (filter_raw_str.size() == 0)
        return process_fn;

    const auto& [ctrl_tok, para] = detail::split_ctrl_tok_para(filter_raw_str);
    using namespace detail::literal;
    switch (hash_djb2a(ctrl_tok.c_str())) {
        case "default"_sh:
            process_fn =
                std::bind(custom_filter::default_value_callback, para, std::placeholders::_1, std::placeholders::_2);
            break;

        case "size"_sh:
            process_fn = custom_filter::size_callback;
            break;

        case "lower"_sh:
            process_fn = custom_filter::lower_callback;
            break;

        case "upper"_sh:
            process_fn = custom_filter::upper_callback;
            break;

        case "length"_sh:
            process_fn = custom_filter::length_callback;
            break;

        default:
            process_fn = [ctrl_tok]([[maybe_unused]] const std::string& var_tok,
                                    [[maybe_unused]] const json& j) -> std::string {
                throw std::runtime_error(std::string("Unsupported filter: ") + ctrl_tok + "\n");
                return "";
            };
            break;
    }

    return process_fn;
}

auto detail::split_ctrl_tok_para(const std::string& filter_raw_str) -> std::tuple<std::string, std::string> {
    // Pattern: {{ [^ ]+ }}
    const auto spilt_pos = filter_raw_str.find(para_delia);

    if (spilt_pos == filter_raw_str.npos)  // Only control token
        return std::make_tuple(filter_raw_str, "");
    else {
        const auto end_of_capture_pos = filter_raw_str.find_first_of(' ', spilt_pos);
        return std::make_tuple(filter_raw_str.substr(0, spilt_pos),
                               filter_raw_str.substr(spilt_pos + 1, end_of_capture_pos - spilt_pos - 1));
    }
}