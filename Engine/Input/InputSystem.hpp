#pragma once

#include <Engine/Input/InputHandler.hpp>
#include <Engine/Input/Event.hpp>

#include <vector>
#include <map>

namespace hx3d {
namespace Input {

class InputSystem {
public:
  InputSystem();

  void registerHandler(InputHandler* p_handler);
  void removeHandler(InputHandler* p_handler);

  bool poll();

private:
  std::map<Event::EventKey, bool> m_keysState;
  std::vector<InputHandler*> m_handlers;
};

}
}
