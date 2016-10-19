#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <string>

namespace hx3d {
namespace Exceptions {

class CriticalError: public Exception {
public:
  CriticalError(const std::string& p_message): m_message(p_message) {}

  virtual const std::string message() const override {
    return m_message;
  }

private:
  std::string m_message;
};

}
}
