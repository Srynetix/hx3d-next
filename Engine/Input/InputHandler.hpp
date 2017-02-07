#pragma once

#include <Engine/Input/Event.hpp>

namespace hx3d {
namespace Input {

class InputHandler {
public:
  virtual void onKeyPress(const Event& p_event) {}
  virtual void onKeyRelease(const Event& p_event) {}
};

}
}
