#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <Engine/Text/Format.hpp>

namespace hx3d {
namespace Exceptions {

class ZipFileStatError: public Exception {
public:
  ZipFileStatError(const U32 p_id):
    Exception(), m_id(p_id) {}

  virtual const std::string message() const override {
    std::string msg = Text::Format("Error on ZipFile::Stat for file n°{}", m_id);
    return msg;
  }

private:
  const U32 m_id;
};

}
}
