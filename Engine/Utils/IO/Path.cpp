#include <Engine/Utils/IO/Path.hpp>

namespace hx3d {
namespace Utils {

std::string dirname(const std::string& p_path) {
  size_t path_length = p_path.size();
  if (path_length == 0 || p_path[path_length - 1] == '\\' || p_path[path_length - 1] == '/') {
    return p_path;
  }

  size_t char_pos = path_length - 1;
  while (char_pos >= 0) {
    char cur = p_path[char_pos];

    if (cur == '/' || cur == '\\') {
      return p_path.substr(char_pos + 1, path_length);
    }

    char_pos--;
  }

  return p_path;
}

std::string basename(const std::string& p_path) {
  size_t path_length = p_path.size();
  if (path_length == 0 || p_path[path_length - 1] == '\\' || p_path[path_length - 1] == '/') {
    return p_path;
  }

  size_t char_pos = path_length - 1;
  while (char_pos >= 0) {
    char cur = p_path[char_pos];

    if (cur == '/' || cur == '\\') {
      if (char_pos != 0) {
        return p_path.substr(0, char_pos - 1);
      }
    }

    char_pos--;
  }

  return p_path;
}

}
}
