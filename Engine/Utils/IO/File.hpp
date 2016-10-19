#pragma once

#include <string>

namespace hx3d {
namespace Utils {

class File {
public:
  File();
  ~File();

  File(const File& p_file);
  File& operator=(const File& p_file);

  const std::string& getContent() const;
  const size_t getSize() const;

  //////////////

  static File loadTextFile(const std::string& p_path);

private:

  static std::string getAssetsPath();

  std::string m_data;
  size_t m_size;
};

}
}
