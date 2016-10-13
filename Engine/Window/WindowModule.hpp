#pragma once

#include <Engine/Core/Module.hpp>

namespace hx3d {

class Window;
class WindowModule: public Module {
public:
  virtual void setUp() override;
  virtual void tearDown() override;

private:
  Window* m_window;
};

}
