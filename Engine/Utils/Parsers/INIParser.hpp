#pragma once

#include <Engine/Utils/Conversion.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>

#include <map>
#include <vector>

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
  void parse(const std::string& p_content);

  template <class Type>
  Type extract(const std::string& p_section, const std::string& p_key) const;

private:
  std::string m_currentSection;
  std::map<std::string, std::map<std::string, std::string>> m_definitions;

  void handleLine(const std::string& p_line);
  std::vector<std::string> split(const std::string& p_line, const char p_delim);
  std::string trim(const std::string& p_line);
};

}
}

#include <Engine/Utils/Parsers/INIParser.inl.hpp>
