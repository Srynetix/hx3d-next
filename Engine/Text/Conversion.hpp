#pragma once

#include <Engine/Text/Exceptions/BadConversion.hpp>
#include <Engine/Core/Types.hpp>

#include <glm/vec4.hpp>
#include <sstream>
#include <typeindex>

namespace hx3d {
namespace Text {

template <class Type>
const Type Convert(const std::string& p_str);

template <class Type>
const std::string ToString(const Type& p_value);

}
}

#include <Engine/Text/Conversion.inl.hpp>
