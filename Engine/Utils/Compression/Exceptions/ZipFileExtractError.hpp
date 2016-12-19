#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <Engine/Text/Format.hpp>

namespace hx3d {
namespace Exceptions {

class ZipFileExtractError: public Exception {
public:
  ZipFileExtractError(const std::string p_str):
    Exception(), m_str(p_str) {}

  virtual const std::string message() const override {
    std::string msg = Text::Format("Error while extracting file {} from Zip", m_str);
    return msg;
  }

private:
  const std::string m_str;
};

}
}
