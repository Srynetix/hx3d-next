#include <Engine/UI/Button.hpp>

namespace hx3d {
namespace UI {

Button::Button() {
  this->setBackgroundColor(Graphics::Color::LightGray);
}

Button::~Button() {
}


void Button::setBackgroundColor(const Graphics::Color& p_color) {
  m_backgroundColor = p_color;
  m_rectangle.setColor(m_backgroundColor);
}

void Button::drawWidget(Graphics::Shader& p_shader) {
  p_shader.sendUniform("u_model", this->getModelMatrix());
  m_rectangle.draw(p_shader);
}

}
}
