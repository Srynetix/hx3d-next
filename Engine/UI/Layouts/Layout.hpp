#pragma once

namespace hx3d {
namespace UI {

class Widget;

namespace Layouts {

class Layout {
public:
  Layout();
  virtual ~Layout();

  virtual void apply(Widget* p_parent) = 0;
};

}
}
}
