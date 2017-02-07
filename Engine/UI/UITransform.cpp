#include <Engine/UI/UITransform.hpp>

namespace hx3d {
namespace UI {

UITransform::UITransform(): m_scalePolicy(kFixed) {}

void UITransform::setScalePolicy(UITransform::ScalePolicy policy) {
  m_scalePolicy = policy;
}

const UITransform::ScalePolicy UITransform::getScalePolicy() const {
  return m_scalePolicy;
}

}
}
