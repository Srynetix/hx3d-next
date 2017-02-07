#include <Engine/UI/Panel.hpp>

namespace hx3d {
namespace UI {

Panel::Panel(): Panel(Graphics::Color::Gray) {}

Panel::Panel(const Graphics::Color& p_backgroundColor): Widget() {
  this->setBackgroundColor(p_backgroundColor);
}

Panel::~Panel() {}

void Panel::setBackgroundColor(const Graphics::Color& p_color) {
  m_backgroundColor = p_color;
  m_rectangle.setColor(m_backgroundColor);
}

void Panel::drawWidget(Graphics::Shader& p_shader) {
  p_shader.sendUniform("u_model", this->getModelMatrix());
  m_rectangle.draw(p_shader);
}

}
}
