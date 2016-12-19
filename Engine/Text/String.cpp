#include <Engine/Text/String.hpp>

#include <algorithm>

namespace hx3d {
namespace Text {

std::string SlugFilename(const std::string& p_filename) {
  std::string newstr = StripExtension(p_filename);
  std::transform(newstr.begin(), newstr.end(), newstr.begin(), [](char p_in) {
    char n = p_in;

    if (n >= 'A' && n <= 'Z') n -= ('Z' - 'z');
    else if (n == '/' || n == '.') n = '-';

    return n;
  });

  return newstr;
}

std::string StripExtension(const std::string& p_filename) {
  return p_filename.substr(0, p_filename.find_last_of("."));
}

}
}
