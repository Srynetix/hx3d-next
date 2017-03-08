#pragma once

#include <Engine/Input/Event.hpp>

namespace hx3d {
namespace Input {

class InputSystem;
class InputHandler {
public:
  virtual void onKeyPress(const Event& p_event) {}
  virtual void onKeyRelease(const Event& p_event) {}

  bool isKeyPressed(const Event::EventKey p_key);

  friend class InputSystem;

private:
  InputSystem* p_system;
};

}
}
