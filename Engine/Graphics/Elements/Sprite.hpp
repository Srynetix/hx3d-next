#pragma once

#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Math/Transform.hpp>

#include <Engine/Graphics/Elements/Shapes/Shape.hpp>

namespace hx3d {
namespace Graphics {

class Texture;
class Shader;
class Sprite: public Math::Transform, public Shape {
public:
  Sprite();
  ~Sprite();

  virtual BaseGeometry& getGeometry() override;
  virtual void draw(Shader& p_shader) override;

  void prepareForFramebuffer(const bool p_value);
  void setTexture(const Utils::SharedPtr<Texture>& p_texture);

private:
  virtual void applyColor() override;

  HX3D_PIMPL
};

}
}
