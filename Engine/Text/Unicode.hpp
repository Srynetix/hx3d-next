#pragma once

#include <Engine/Core/Types.hpp>
#include <vector>

namespace hx3d {
namespace Text {

std::vector<U16> ToUTF16(const std::string& p_string);
std::vector<U32> ToUTF32(const std::string& p_string);

}
}
