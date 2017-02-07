#pragma once

#include <memory>

namespace hx3d {
namespace Utils {

template <class Type>
using SharedPtr = std::shared_ptr<Type>;
template <class Type>
using UniquePtr = std::unique_ptr<Type>;
template <class Type>
using WeakPtr = std::weak_ptr<Type>;

template <class Type, class... Args>
UniquePtr<Type> MakeUniquePtr(Args&&... args) {
  return std::unique_ptr<Type>(new Type(std::forward<Args>(args)...));
}

template <class Type, class... Args>
SharedPtr<Type> MakeSharedPtr(Args&&... args) {
  return std::make_shared<Type>(std::forward<Args>(args)...);
}

}
}

#define HX3D_CREATE_ENABLE(Type) \
  using UPtr = Utils::UniquePtr<Type>; \
  template <class... Args> \
  static Utils::UniquePtr<Type> Create(Args&&... p_args) { \
    return Utils::MakeUniquePtr<Type>(std::forward<Args>(p_args)...); \
  }

#define HX3D_PIMPL \
  struct Impl; \
  Utils::UniquePtr<Impl> m_impl;

#define HX3D_PIMPL_INIT() m_impl(Utils::MakeUniquePtr<Impl>())
