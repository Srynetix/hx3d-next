#pragma once

#include <memory>

namespace hx3d {
namespace Utils {

template <class Type, class... Args>
std::unique_ptr<Type> MakeUniquePtr(Args&&... args);

}
}

#include <Engine/Utils/Memory/SmartPtrs.inl.hpp>
