#include <Engine/Graphics/Elements/Color.hpp>

#include <Engine/Math/Random.hpp>

namespace hx3d {
namespace Graphics {

Color::Color(const U8 p_r, const U8 p_g, const U8 p_b, const U8 p_a):
  m_r(p_r), m_g(p_g), m_b(p_b), m_a(p_a), m_floatValues(p_r / 255.f, p_g / 255.f, p_b / 255.f, p_a / 255.f) {}

Color& Color::operator=(const Color& p_color) {
  if (p_color != *this) {
    m_r = p_color.red();
    m_g = p_color.green();
    m_b = p_color.blue();
    m_a = p_color.alpha();

    m_floatValues = p_color.m_floatValues;
  }

  return *this;
}

const U8 Color::red() const {
  return m_r;
}

const U8 Color::green() const {
  return m_g;
}

const U8 Color::blue() const {
  return m_b;
}

const U8 Color::alpha() const {
  return m_a;
}

void Color::setRed(const U8 p_value) {
  if (m_r != p_value) {
    m_r = p_value;
    m_floatValues.x = m_r / 255.f;
  }
}

void Color::setGreen(const U8 p_value) {
  if (m_g != p_value) {
    m_g = p_value;
    m_floatValues.y = m_g / 255.f;
  }
}

void Color::setBlue(const U8 p_value) {
  if (m_b != p_value) {
    m_b = p_value;
    m_floatValues.z = m_b / 255.f;
  }
}

void Color::setAlpha(const U8 p_value) {
  if (m_a != p_value) {
    m_a = p_value;
    m_floatValues.w = m_a / 255.f;
  }
}

void Color::setColor(const U8 p_r, const U8 p_g, const U8 p_b) {
  m_r = p_r;
  m_g = p_g;
  m_b = p_b;

  m_floatValues.x = p_r / 255.f;
  m_floatValues.y = p_g / 255.f;
  m_floatValues.z = p_b / 255.f;
}

void Color::setColor(const U8 p_r, const U8 p_g, const U8 p_b, const U8 p_a) {
  setColor(p_r, p_g, p_b);
  m_a = p_a;

  m_floatValues.w = p_a / 255.f;
}

void Color::setColor(const Color& p_color) {
  *this = p_color;
}

const glm::vec4& Color::getFloatValues() const {
  return m_floatValues;
}

Color Color::GenerateRandomColor(bool randomAlpha) {
  return Color(
    Math::Random::randrange(0, 255),
    Math::Random::randrange(0, 255),
    Math::Random::randrange(0, 255),
    randomAlpha ? Math::Random::randrange(0, 255) : 255
  );
}

bool operator==(const Color& p_lhs, const Color& p_rhs) {
  return (
    p_lhs.red() == p_rhs.red() &&
    p_lhs.green() == p_rhs.green() &&
    p_lhs.blue() == p_rhs.blue() &&
    p_lhs.alpha() == p_rhs.alpha()
  );
}

bool operator!=(const Color& p_lhs, const Color& p_rhs) {
  return !(p_lhs == p_rhs);
}

Color Color::Black = Color(0, 0, 0, 255);
Color Color::White = Color(255, 255, 255, 255);
Color Color::Red = Color(255, 0, 0, 255);
Color Color::Green = Color(0, 255, 0, 255);
Color Color::Blue = Color(0, 0, 255, 255);
Color Color::Gray = Color(127, 127, 127, 255);

}
}
