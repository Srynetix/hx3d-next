#pragma once

namespace hx3d {
namespace Utils {

template <class Type>
class SingletonHolder {
public:
  static Type& Instance() {
    if (!p_instance) {
      p_instance = new Type();
    }

    return *p_instance;
  }

  static void Initialize() {
    if (!p_instance) {
      p_instance = new Type();
    }
  }

  static void Release() {
    if (p_instance) {
      delete p_instance;
    }

    p_instance = nullptr;
  }

protected:
  SingletonHolder() = delete;
  ~SingletonHolder() = delete;

  SingletonHolder(const SingletonHolder& obj) = delete;
  SingletonHolder(const SingletonHolder&& obj) = delete;
  SingletonHolder& operator=(const SingletonHolder& obj) = delete;
  SingletonHolder& operator=(const SingletonHolder&& obj) = delete;

  static Type* p_instance;
};

template <class Type>
Type* SingletonHolder<Type>::p_instance = nullptr;

}
}
