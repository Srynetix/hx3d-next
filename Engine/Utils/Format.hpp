#pragma once

#include <string>

namespace hx3d {
namespace Utils {

template <class... Args, class Current>
std::string Format(const std::string& p_str, const Current& p_val, Args&&... args);

}
}

#include <Engine/Utils/Format.inl.hpp>
