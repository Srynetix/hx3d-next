#pragma once

#include <Engine/Core/Types.hpp>
#include <glm/vec4.hpp>

namespace hx3d {
namespace Graphics {

class Color {
public:
  explicit Color(const U8 p_r = 0, const U8 p_g = 0, const U8 p_b = 0, const U8 p_a = 255);

  Color& operator=(const Color& p_color);

  const U8 red() const;
  const U8 green() const;
  const U8 blue() const;
  const U8 alpha() const;

  void setRed(const U8 p_value);
  void setGreen(const U8 p_value);
  void setBlue(const U8 p_value);
  void setAlpha(const U8 p_value);

  void setColor(const Color& p_color);
  void setColor(const U8 p_r, const U8 p_g, const U8 p_b);
  void setColor(const U8 p_r, const U8 p_g, const U8 p_b, const U8 p_a);

  const glm::vec4& getFloatValues() const;

  static Color GenerateRandomColor(bool randomAlpha = false);

  // Base colors
  static Color Black;
  static Color White;
  static Color Red;
  static Color Green;
  static Color Blue;
  static Color Gray;

private:
  U8 m_r;
  U8 m_g;
  U8 m_b;
  U8 m_a;

  glm::vec4 m_floatValues;
};

bool operator==(const Color& p_lhs, const Color& p_rhs);
bool operator!=(const Color& p_lhs, const Color& p_rhs);

}
}
