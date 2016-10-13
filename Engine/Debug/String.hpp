#pragma once

#include <string>
#include <cstdarg>

namespace hx3d {

const std::string format(const char* p_fmt, ...);
const std::string format(const char* p_fmt, va_list p_args);

template <class Type>
const std::string to_string(const Type p_value);

}

#include <Engine/Debug/String.inl.hpp>
