#pragma once

#include <string>

namespace hx3d {
namespace Utils {

class FileHandler;
class File {
public:
  File();
  ~File();

  enum ContentType {
    kASCII,
    kBinary
  };

  File(File&& p_file);
  File& operator=(File&& p_file);

  char* getContent() const;
  unsigned char* getUContent() const;
  const std::string& getStrContent() const;
  const size_t getSize() const;

  void setRawValues(char* p_data, const size_t p_size, const ContentType p_type);

  //////////////

  friend class FileHandler;

private:
  static File loadFile(const std::string& p_path, const ContentType p_type = kASCII);
  static std::string getAssetsPath();

  char* m_data;
  size_t m_size;
  ContentType m_type;
  std::string m_string;
};

}
}
