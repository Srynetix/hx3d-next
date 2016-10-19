/**
Base Exception class.
**/

#pragma once

#include <string>
#include <exception>

namespace hx3d {
namespace Exceptions {

class Exception: public std::exception {
public:
  Exception(): m_message("") {}

  virtual const std::string message() const = 0;

  virtual const char* what() const throw() override {
    m_message = "[Exception] " + this->message();
    return m_message.c_str();
  }

private:
  mutable std::string m_message;
};

}
}
