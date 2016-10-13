#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <Engine/Debug/String.hpp>

namespace hx3d {
namespace exceptions {

template <class Type, class Key>
class NotFound: public Exception {
public:
  NotFound(Key p_key):
    Exception(), m_key(p_key) {}

  virtual const std::string message() const override {
    return format("Key not found: ") + to_string(m_key);
  }

private:
  Key m_key;
};

}
}
