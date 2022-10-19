#ifndef DJANGO_ENGINE_DJANGO_HPP_
#define DJANGO_ENGINE_DJANGO_HPP_

#include <module.hpp>
#include <string>

namespace Django
{
    Module parse(const std::string &filepath);
};

#endif