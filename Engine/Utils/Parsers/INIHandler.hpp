#pragma once

#include <string>
#include <memory>

namespace hx3d {
namespace Utils {

class INIParser;
class INIHandler {
public:
  INIHandler();
  ~INIHandler();

  void parseFromFile(const std::string& p_path);
  const INIParser& getParser() const;

private:
  struct Impl;
  std::unique_ptr<Impl> m_impl;
};

}
}
