#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <Engine/Text/Format.hpp>

namespace hx3d {
namespace Exceptions {

template <class TypeSrc, class TypeDst>
class BadConversion: public Exception {
public:
  BadConversion(const TypeSrc& p_err):
    Exception(), m_err(p_err) {}

  virtual const std::string message() const override {
    std::string msg = Text::Format("Conversion error from %s to %s: ", GetTypename<TypeSrc>(), GetTypename<TypeDst>()) + Text::ToString(m_err);

    return msg;
  }

private:
  TypeSrc m_err;
};

}
}
