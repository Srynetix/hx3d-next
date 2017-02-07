#pragma once

#include <Engine/Graphics/Elements/Shapes/Rectangle.hpp>
#include <Engine/UI/Widget.hpp>

namespace hx3d {
namespace UI {

class Panel: public Widget {
public:
  HX3D_CREATE_ENABLE(Panel)

  Panel();
  Panel(const Graphics::Color& p_backgroundColor);
  ~Panel();

  void setBackgroundColor(const Graphics::Color& p_color);

  virtual void drawWidget(Graphics::Shader& p_shader) override;

private:

  Graphics::Rectangle m_rectangle;
  Graphics::Color m_backgroundColor;
};

}
}
