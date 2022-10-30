#include <module.hpp>
#include <nlohmann/json.hpp>
#include <parser/parser.hpp>
#include <stdexcept>
#include <string_view>

using nlohmann::json;

namespace detail {
json parse(const std::string& str);

namespace helper {
std::string strip_comments(const std::string& s);
}
}  // namespace detail

struct Django::Module::Impl {
    Impl() = default;
    Impl(const std::string& filepath);

    const std::string filepath;
    const std::string context;
    json contents;
};

Django::Module::Impl::Impl(const std::string& filepath_)
    : filepath{filepath_}, context{parser::extend_templates(filepath_)}, contents{detail::parse(context)} {}

Django::Module::Module() : pImpl{std::make_unique<Django::Module::Impl>()} {}
Django::Module::~Module() {}

Django::Module::Module(const std::string& filepath) : pImpl{std::make_unique<Django::Module::Impl>(filepath)} {}

std::string Django::Module::to_string() const noexcept {
    return pImpl->contents.dump();
}

json detail::parse(const std::string& str) {
    // Strip all comments
    const auto& stripped = helper::strip_comments(str);

    // Freeze the origin placeholder there
    // We register another information about the placeholder
    json j = json::object();

    // Find variable
    j["variable"] = parser::find_variables(stripped);

    return j;
}

std::string detail::helper::strip_comments(const std::string& str) {
    // comment format: {# .* #}
    // https://docs.djangoproject.com/en/4.1/ref/templates/language/#comments
    // It is open-close style qouting

    static const std::string_view comment_beg{"{#"};
    static const std::string_view comment_end{"#}"};

    std::string ret;
    ret.reserve(str.size());

    for (size_t cur = 0; cur <= str.size();) {
        const size_t start = cur;
        size_t stop = str.size();

        size_t opened = str.find(comment_beg, cur);
        if (opened != std::string::npos) {  // Opned
            stop = str.find(comment_end, cur);

            if (stop == std::string::npos) [[unlikely]]
                throw std::runtime_error("Missing closing comment!");

            ret.append(str.begin() + start, str.begin() + opened);
        } else {
            // Opened is npos
            ret.append(str.begin() + start, str.end());
            break;
        }

        // Has a comment
        cur = stop + comment_end.size();
    }

    return ret;
}
