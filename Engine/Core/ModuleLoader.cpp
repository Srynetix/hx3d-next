#include <Engine/Core/ModuleLoader.hpp>
#include <Engine/Core/Module.hpp>

#include <Engine/Core/Exceptions/KeyNotFound.hpp>

#include <map>
#include <deque>

namespace hx3d {
namespace Core {

struct ModuleLoader::Impl {
	std::deque<std::type_index> m_indices;
	std::map<std::type_index, Module*> m_modules;
};

ModuleLoader::ModuleLoader():
  HX3D_PIMPL_INIT() {}

ModuleLoader::~ModuleLoader() {
  while (!m_impl->m_indices.empty()) {
    auto& elem = m_impl->m_indices.back();
    m_impl->m_indices.pop_back();

    m_impl->m_modules[elem]->tearDown();

    delete m_impl->m_modules[elem];
    m_impl->m_modules.erase(elem);
  }
}

Module* ModuleLoader::internal_get(const std::type_index& p_type) {
  if (m_impl->m_modules.find(p_type) == m_impl->m_modules.end()) {
    throw Exceptions::KeyNotFound<ModuleLoader, std::type_index>(p_type);
  }

  return m_impl->m_modules[p_type];
}

void ModuleLoader::internal_set(const std::type_index& p_type, Module* p_module) {
  m_impl->m_indices.push_back(p_type);
  m_impl->m_modules[p_type] = p_module;
}

bool ModuleLoader::exists(const std::type_index& p_type) {
  return (m_impl->m_modules.find(p_type) != m_impl->m_modules.end());
}

}
}
