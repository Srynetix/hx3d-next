#include <Engine/Core/ModuleLoader.hpp>
#include <Engine/Core/Module.hpp>

namespace hx3d {
namespace Core {

ModuleLoader::ModuleLoader(Engine *p_engine):
  m_engine(p_engine) {}

ModuleLoader::~ModuleLoader() {}

void ModuleLoader::startModule(Module* module) {
  if (module) {
    module->setUp(m_engine);
  }
}

void ModuleLoader::endModule(Module* module) {
  if (module) {
    module->tearDown();
  }
}

}
}
