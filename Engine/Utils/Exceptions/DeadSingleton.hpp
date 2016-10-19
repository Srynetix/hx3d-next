#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>

namespace hx3d {
namespace Exceptions {

class DeadSingleton: public Exception {
public:
  DeadSingleton():
    Exception() {}

  virtual const std::string message() const override {
    return "Trying to access to a dead singleton";
  }
};

}
}
