#pragma once

namespace hx3d {
namespace Core {

class Engine;
class Module {
public:
	virtual void setUp(Engine* p_engine) = 0;
	virtual void tearDown() = 0;
};

}
}
