#include <Engine/Text/Unicode.hpp>
#include <utf8.h>

namespace hx3d {
namespace Text {

std::vector<U16> ToUTF16(const std::string& p_string) {
  std::vector<U16> utf16line;
  utf8::utf8to16(p_string.begin(), p_string.end(), std::back_inserter(utf16line));
  return utf16line;
}

std::vector<U32> ToUTF32(const std::string& p_string) {
  std::vector<U32> utf32line;
  utf8::utf8to32(p_string.begin(), p_string.end(), std::back_inserter(utf32line));
  return utf32line;
}

}
}
