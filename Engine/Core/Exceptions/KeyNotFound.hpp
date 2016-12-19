#pragma once

#include <Engine/Core/Exceptions/Exception.hpp>
#include <Engine/Text/Format.hpp>

namespace hx3d {
namespace Exceptions {

template <class Type, class Key>
class KeyNotFound: public Exception {
public:
  KeyNotFound(Key p_key, const char* p_additionalInfo = nullptr):
    Exception(), m_key(Text::ToString(p_key)), m_additionalInfo(p_additionalInfo) {}

  virtual const std::string message() const override {
    std::string msg = Text::Format("Key `%s` not found in %s.", m_key, GetTypename<Type>());

    if (m_additionalInfo) {
      msg += Text::Format(" (%s)", m_additionalInfo);
    }

    return msg;
  }

private:
  std::string m_key;
  const char* m_additionalInfo;
};

}
}
