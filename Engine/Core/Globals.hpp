#pragma once

#include <Engine/Utils/Uncopyable.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <string>

namespace hx3d {
namespace Core {

class Globals: public Utils::Uncopyable {
public:
  Globals();
  ~Globals();

  template <class T>
  const T& get(const std::string& p_name) const {
    return *static_cast<const T*>(internal_get(p_name));
  }

  template <class T>
  void set(const std::string& p_name, T p_val) {
    if (!exists(p_name)) {
      internal_set(p_name, new T(p_val));
    } else {
      auto ptr = internal_get(p_name);
      *static_cast<T*>(ptr) = p_val;
    }
  }

  bool exists(const std::string& p_name) const;

private:
  HX3D_PIMPL

  const void* internal_get(const std::string& p_name) const;
  void* internal_get(const std::string& p_name);
  void internal_set(const std::string& p_name, void* p_data);
};

}
}

#define HX3D_GLOB_SET(n, v) Root::Instance().getGlobals().set(n, v)
#define HX3D_GLOB_GET(n, t) Root::Instance().getGlobals().get<t>(n)
