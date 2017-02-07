#include <Engine/UI/Layouts/BoxLayout.hpp>
#include <Engine/UI/Widget.hpp>

#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace UI {
namespace Layouts {

BoxLayout::BoxLayout(Type p_type): m_type(p_type) {}
BoxLayout::~BoxLayout() {}

void BoxLayout::apply(Widget* p_parent) {
  assert(p_parent);

  // Align all children
  if (m_type == kHorizontal) {
    this->horizontalAlign(p_parent);
  } else {
    this->verticalAlign(p_parent);
  }
}

void BoxLayout::verticalAlign(Widget* p_parent) {
  auto parentScale = p_parent->getScale();
  auto parentPosition = p_parent->getPosition();
  auto& children = p_parent->getChildren();
  auto childCount = children.size();

  auto childWidth = parentScale.x;
  auto childHeight = parentScale.y / childCount;

  auto normalizedY = parentPosition.y + parentScale.y / 2;
  auto childY = normalizedY - childHeight / 2;

  for (auto& child: children) {
    if (child->getScalePolicy() == UITransform::kExpand) {
      child->setScale(childWidth, childHeight);
    } else if (child->getScalePolicy() == UITransform::kExpandWidth) {
      child->setScale(childWidth, child->getScale().y);
    } else if (child->getScalePolicy() == UITransform::kExpandHeight) {
      child->setScale(child->getScale().x, childHeight);
    }

    child->setPosition(parentPosition.x, childY);
    childY -= childHeight;
  }
}

void BoxLayout::horizontalAlign(Widget* p_parent) {
  auto parentScale = p_parent->getScale();
  auto parentPosition = p_parent->getPosition();
  auto& children = p_parent->getChildren();
  auto childCount = children.size();

  auto childWidth = parentScale.x / childCount;
  auto childHeight = parentScale.y;

  auto normalizedX = parentPosition.x - parentScale.x / 2;
  auto childX = normalizedX + childWidth / 2;

  for (auto& child: children) {
    if (child->getScalePolicy() == UITransform::kExpand) {
      child->setScale(childWidth, childHeight);
    } else if (child->getScalePolicy() == UITransform::kExpandWidth) {
      child->setScale(childWidth, child->getScale().y);
    } else if (child->getScalePolicy() == UITransform::kExpandHeight) {
      child->setScale(child->getScale().x, childHeight);
    }

    child->setPosition(childX, parentPosition.y);
    childX += childWidth;
  }
}

}
}
}
