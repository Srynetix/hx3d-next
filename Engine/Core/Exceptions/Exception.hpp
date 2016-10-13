/**
Base Exception class.
**/

#pragma once

#include <Engine/Debug/String.hpp>

#include <exception>

namespace hx3d {
namespace exceptions {

class Exception: public std::exception {
public:
  Exception(): m_message("") {}

  virtual const std::string message() const = 0;

  virtual const char* what() const throw() override {
    m_message = this->message();
    return m_message.c_str();
  }

private:
  mutable std::string m_message;
};

}
}
