#pragma once

#include <Engine/Graphics/Elements/Drawable.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <Engine/UI/UITransform.hpp>
#include <Engine/UI/Layouts/Layout.hpp>

#include <vector>

namespace hx3d {
namespace UI {

class Widget: public Graphics::Drawable, public UITransform {
public:
  HX3D_CREATE_ENABLE(Widget)

  Widget();
  virtual ~Widget();

  template <class T, class... Args>
  void makeLayout(Args&&... p_args) {
    m_layout = Utils::MakeUniquePtr<T>(std::forward<Args>(p_args)...);
  }

  template <class Type>
  void moveWidget(Utils::UniquePtr<Type>& p_widget) {
    p_widget->m_parent = this;
    m_children.push_back(std::move(p_widget));
  }

  template <class Type, class... Args>
  Widget* makeWidget(Args&&... p_args) {
    auto ptr = Utils::MakeUniquePtr<Type>(std::forward<Args>(p_args)...);
    auto rptr = ptr.get();

    ptr->m_parent = this;
    m_children.push_back(std::move(ptr));

    return rptr;
  }

  void applyLayout();

  const std::vector<Utils::UniquePtr<Widget>>& getChildren() const {
    return m_children;
  }

  virtual void draw(Graphics::Shader& p_shader) override;

  virtual void drawWidget(Graphics::Shader& p_shader) = 0;

protected:
  Widget* m_parent;
  std::vector<Utils::UniquePtr<Widget>> m_children;
  Utils::UniquePtr<Layouts::Layout> m_layout;
};

}
}
