#include <Engine/Core/ModuleLoader.hpp>
#include <Engine/Core/Module.hpp>

namespace hx3d {

ModuleLoader::ModuleLoader() {
}

ModuleLoader::~ModuleLoader() {
}

void ModuleLoader::startModule(Module* module) {
  if (module) {
    module->setUp();
  }
}

void ModuleLoader::endModule(Module* module) {
  if (module) {
    module->tearDown();
  }
}

}
