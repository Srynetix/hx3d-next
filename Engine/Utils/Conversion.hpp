#pragma once

#include <string>

namespace hx3d {
namespace Utils {

template <class Type>
const Type Convert(const std::string& p_str);

template <class Type>
const std::string ToString(const Type p_value);

}
}

#include <Engine/Utils/Conversion.inl.hpp>
