#pragma once

namespace hx3d {
namespace Core {

class Engine;
class Module;
class ModuleLoader {
public:
	ModuleLoader(Engine* p_engine);
	~ModuleLoader();

	void startModule(Module* module);
	void endModule(Module* module);

private:
	Engine* m_engine;
};

}
}
