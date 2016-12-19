#pragma once

#include <memory>

namespace hx3d {
namespace Utils {

template <class Type, class... Args>
std::unique_ptr<Type> MakeUniquePtr(Args&&... args) {
  return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}

template <class Type, class... Args>
std::shared_ptr<Type> MakeSharedPtr(Args&&... args) {
  return std::make_shared<Type>(std::forward<Args>(args)...);
}

}
}

#define HX3D_PIMPL \
  struct Impl; \
  std::unique_ptr<Impl> m_impl;

#define HX3D_PIMPL_INIT() m_impl(Utils::MakeUniquePtr<Impl>())
