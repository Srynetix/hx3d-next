#pragma once

#include <Engine/Core/Types.hpp>

namespace hx3d {
namespace Utils {

class Chronometer {
public:
  Chronometer(const F32 p_timeout = 1.f);

  void setTimeout(const F32 p_timeout);
  void tick(const F32 p_delta);
  void reset();

  const F32 getElapsedTime() const;
  bool isTimeout() const;

private:
  F32 m_elapsed;
  F32 m_timeout;
};

}
}
