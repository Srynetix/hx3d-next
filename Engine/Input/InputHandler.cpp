#include <Engine/Input/InputHandler.hpp>
#include <Engine/Input/InputSystem.hpp>

namespace hx3d {
namespace Input {

bool InputHandler::isKeyPressed(const Event::EventKey p_key) {
  return p_system && p_system->isKeyPressed(p_key);
}

}
}
