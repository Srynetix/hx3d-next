#pragma once

#include <Engine/Math/Transform.hpp>

namespace hx3d {
namespace UI {

class UITransform: public Math::Transform {
public:
  UITransform();

  enum ScalePolicy {
    kFixed,
    kExpand,
    kExpandWidth,
    kExpandHeight
  };

  const ScalePolicy getScalePolicy() const;
  void setScalePolicy(ScalePolicy policy);

private:
  ScalePolicy m_scalePolicy;
};

}
}
