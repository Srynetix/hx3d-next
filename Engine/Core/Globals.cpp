#include <Engine/Core/Globals.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>

#include <map>

namespace hx3d {
namespace Core {

struct Globals::Impl {
  std::map<std::string, void*> m_variables;
};

Globals::Globals():
  HX3D_PIMPL_INIT() {}

Globals::~Globals() {
  for (auto it = m_impl->m_variables.begin(); it != m_impl->m_variables.end(); ++it) {
    if (it->second) {
      delete it->second;
    }
  }

  m_impl->m_variables.clear();
}

const void* Globals::internal_get(const std::string& p_name) const {
  if (m_impl->m_variables.find(p_name) == m_impl->m_variables.end()) {
    throw Exceptions::KeyNotFound<Globals, std::string>(p_name);
  } else {
    return m_impl->m_variables[p_name];
  }
}

void* Globals::internal_get(const std::string& p_name) {
  if (m_impl->m_variables.find(p_name) == m_impl->m_variables.end()) {
    throw Exceptions::KeyNotFound<Globals, std::string>(p_name);
  } else {
    return m_impl->m_variables[p_name];
  }
}


void Globals::internal_set(const std::string& p_name, void* p_data) {
  m_impl->m_variables[p_name] = p_data;
}

bool Globals::exists(const std::string& p_name) const {
  return (m_impl->m_variables.find(p_name) != m_impl->m_variables.end());
}

}
}
