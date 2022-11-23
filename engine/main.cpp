#include <Django.hpp>
#include <iostream>

int main() {
    auto nothing = Django::parse("../template/sample.html");
    std::cout << nothing.to_string() << std::endl;

    nothing.set("foo", nlohmann::json(std::to_string(123) + "Success"));
    std::cout << nothing.to_string() << std::endl;

    try {
        nothing.set("THIS_IS_INVALID_DUMMY_KEY", nlohmann::json("INVALID_VALUE"));
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    const auto& foo_ = nothing.get("foo");
    if (foo_.has_value())
        std::cout << foo_.value() << std::endl;

    const auto& res = nothing.render();
    std::cout << res << std::endl;

    return 0;
}