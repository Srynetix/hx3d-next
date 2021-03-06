#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <Engine/Text/Format.hpp>

namespace hx3d {
namespace Exceptions {

class FileNotFound: public Exception {
public:
  FileNotFound(const std::string p_file):
    Exception(), m_file(p_file) {}

  virtual const std::string message() const override {
    std::string msg = Text::Format("File not found: `%s`", m_file);
    return msg;
  }

private:
  const std::string m_file;
};

}
}
