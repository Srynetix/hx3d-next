#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Text/Conversion.hpp>

namespace hx3d {
namespace Utils {

/**
# Simple INI Parser

**Syntax**

```
[section1]

key1 = val1
key2 = val2

[section2]

key1 = val1
```

**/
class INIParser {

public:
  INIParser(const std::string& p_content = "");
  ~INIParser();

  void parse(const std::string& p_content);

  template <class Type>
  Type extract(const std::string& p_section, const std::string& p_key) const {
    return Text::Convert<Type>(extract_value(p_section, p_key));
  }

private:
  struct Impl;
  std::unique_ptr<Impl> m_impl;

  const std::string& INIParser::extract_value(const std::string& p_section, const std::string& p_key) const;
};

}
}
