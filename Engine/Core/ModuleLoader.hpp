#pragma once

#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <typeindex>

namespace hx3d {
namespace Core {

class Module;
class ModuleLoader {
public:
	ModuleLoader();
	~ModuleLoader();

	template <class ModuleType, class... Args>
	void loadModule(Args&&... p_args) {
		auto& type = std::type_index(typeid(ModuleType));
		if (!exists(type)) {
			auto module = new ModuleType(p_args...);
			module->setUp();

			internal_set(type, module);
		}
	}

	template <class ModuleType>
	ModuleType& getModule() {
		auto& type = std::type_index(typeid(ModuleType));
		return *static_cast<ModuleType*>(internal_get(type));
	}

	bool exists(const std::type_index& p_type);

private:
	HX3D_PIMPL

	void internal_set(const std::type_index& p_type, Module* p_module);
	Module* internal_get(const std::type_index& p_type);
};

}
}
