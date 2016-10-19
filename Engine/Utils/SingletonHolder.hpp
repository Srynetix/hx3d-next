#pragma once

namespace hx3d {
namespace Utils {

template <class Type>
class SingletonHolder {
public:
  static Type& Instance();
  static void Release();

protected:
  SingletonHolder() = delete;
  ~SingletonHolder() = delete;

  SingletonHolder(const SingletonHolder& obj) = delete;
  SingletonHolder(const SingletonHolder&& obj) = delete;
  SingletonHolder& operator=(const SingletonHolder& obj) = delete;
  SingletonHolder& operator=(const SingletonHolder&& obj) = delete;

  static Type* p_instance;
};

}
}

#include <Engine/Utils/SingletonHolder.inl.hpp>
