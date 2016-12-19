#pragma once

namespace hx3d {
namespace Utils {

class Uncopyable {
public:
  Uncopyable() {}

private:
  Uncopyable(const Uncopyable&) = delete;
  Uncopyable& operator=(const Uncopyable&) = delete;

  Uncopyable(Uncopyable&&) = default;
  Uncopyable& operator=(Uncopyable&&) = default;
};

}
}
