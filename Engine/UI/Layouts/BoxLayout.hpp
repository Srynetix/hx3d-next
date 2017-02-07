#pragma once

#include <Engine/UI/Layouts/Layout.hpp>

namespace hx3d {
namespace UI {
namespace Layouts {

class BoxLayout: public Layout {
public:
  enum Type {
    kHorizontal,
    kVertical
  };

  BoxLayout(Type p_type);
  ~BoxLayout();

  virtual void apply(Widget* p_parent) override;

private:
  Type m_type;

  void verticalAlign(Widget* p_parent);
  void horizontalAlign(Widget* p_parent);
};

}
}
}
