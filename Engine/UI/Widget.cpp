#include <Engine/UI/Widget.hpp>

namespace hx3d {
namespace UI {

Widget::Widget():
  m_parent(nullptr), m_layout(nullptr)
{}

Widget::~Widget() {}

void Widget::applyLayout() {
  // Use layout to place the element
  if (m_layout) {
    m_layout->apply(this);
  }
}

void Widget::draw(Graphics::Shader& p_shader) {
  // Draw parent then draw children
  drawWidget(p_shader);

  for (auto& child: m_children) {
    child->draw(p_shader);
  }
}

}
}
