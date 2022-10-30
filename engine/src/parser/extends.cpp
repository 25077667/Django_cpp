#include <boost/regex.hpp>
#include <fstream>
#include <parser/extends.hpp>

namespace detail {
std::string file_to_string(const std::string& filename);
// std::string extend_string_template(const std::string& ctx);
std::string extend_templates_impl(const std::string& associated_dir, const std::string& ctx);
std::vector<std::string> get_base_template_name(const std::string& associated_dir, const std::string& ctx);
std::string get_related_path(const std::string& filepath);
}  // namespace detail

std::string parser::extend_templates(const std::string& filename) {
    // Extended templates should be starred from the "same" related directory
    const auto& path = detail::get_related_path(filename);
    return detail::extend_templates_impl(path, detail::file_to_string(filename));
}

std::string detail::file_to_string(const std::string& filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open())
        throw std::runtime_error("file could not be opened!\n");

    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

std::string detail::extend_templates_impl(const std::string& associated_dir, const std::string& ctx) {
    // https://docs.djangoproject.com/en/4.1/ref/templates/language/#template-inheritance
    // Recursively extend referenced base templates

    std::list<std::string> base_templates_ctx;
    const auto& gen = detail::get_base_template_name(associated_dir, ctx);
    for (const auto& base_filename : gen) {  // Find all basis in the current template
        const auto& base_ctx = parser::extend_templates(base_filename);
        base_templates_ctx.emplace_front(std::move(base_ctx));
    }

    // See this example
    // echo "abcffffabcffffabc" | sed 's/\(.*\)ffff\(.*\)/\1\2/'
    // abcffffabcabc
    // Longest matching pattern would match the earliest matched pattern
    static const boost::regex expr{"(.*){% extends \".+\" %}(.*)"};
    std::string canvas = ctx;
    while (1) {
        //TODO: Improve performance here
        boost::match_results<std::string::iterator> what;
        if (boost::regex_search(canvas.begin(), canvas.end(), what, expr, boost::match_default) == false)
            break;  // Not found
        canvas = what[1] + base_templates_ctx.front() + what[2];
        base_templates_ctx.pop_front();
    }

    return canvas;
}

std::vector<std::string> detail::get_base_template_name(const std::string& associated_dir, const std::string& ctx) {
    std::vector<std::string> filename_list;

    // Format:
    // {% extends "base.html" %}
    static const boost::regex expr{"{% extends \"([\\w\\.]+)\" %}"};
    boost::sregex_iterator m1(ctx.begin(), ctx.end(), expr);
    boost::sregex_iterator m2;
    std::for_each(m1, m2, [&filename_list, &associated_dir](const auto& what) {
        filename_list.emplace_back(associated_dir + what[1].str());
    });

    return filename_list;
}

std::string detail::get_related_path(const std::string& filepath) {
    const auto& split_pos = filepath.find_last_of('/');
    if (split_pos == filepath.npos)
        return "./";
    else
        return filepath.substr(0, split_pos) + "/";
}