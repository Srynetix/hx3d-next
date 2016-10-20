#pragma once

namespace hx3d {
namespace Core {

class Module {
public:
	virtual void setUp() = 0;
	virtual void tearDown() = 0;
};

}
}
