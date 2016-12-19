#include <Engine/Utils/Time/Chronometer.hpp>

namespace hx3d {
namespace Utils {

Chronometer::Chronometer(const F32 p_timeout):
  m_timeout(p_timeout), m_elapsed(0.f) {}

void Chronometer::setTimeout(const F32 p_timeout) {
  m_timeout = p_timeout;
  reset();
}

void Chronometer::reset() {
  m_elapsed = 0.f;
}

void Chronometer::tick(const F32 p_delta) {
  m_elapsed += p_delta;
}

bool Chronometer::isTimeout() const {
  return m_elapsed >= m_timeout;
}

const F32 Chronometer::getElapsedTime() const {
  return m_elapsed;
}

}
}
