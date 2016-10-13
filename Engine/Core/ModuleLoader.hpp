#pragma once

namespace hx3d {

class Module;
class ModuleLoader {
public:
	ModuleLoader();
	~ModuleLoader();

	void startModule(Module* module);
	void endModule(Module* module);
};

}
