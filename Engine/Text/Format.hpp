#pragma once

#include <string>
#include <regex>

#include <Engine/Core/Types.hpp>
#include <Engine/Text/Conversion.hpp>

#include <glm/vec4.hpp>

namespace hx3d {
namespace Text {

template <class... Args, class Current>
std::string Format(const std::string& p_str, const Current& p_val, Args&&... p_args);

}
}

#include <Engine/Text/Format.inl.hpp>
