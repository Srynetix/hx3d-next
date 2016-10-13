#include <Engine/Debug/String.hpp>

#include <cstring>

namespace hx3d {

const std::string format(const char* p_fmt, ...) {
  int size = ((int)strlen(p_fmt)) * 2 + 65536;   // Use a rubric appropriate for your code
  std::string str;
  va_list ap;
  while (1) {     // Maximum two passes on a POSIX system...
    str.resize(size);
    va_start(ap, p_fmt);
    int n = vsnprintf((char *)str.data(), size, p_fmt, ap);
    va_end(ap);
    if (n > -1 && n < size) {  // Everything worked
      str.resize(n);
      return str;
    }
    if (n > -1)  // Needed size returned
      size = n + 1;   // For null char
    else
      size *= 2;      // Guess at a larger size (OS specific)
  }

  return str;
}

const std::string format(const char* p_fmt, va_list p_args) {
  int size = ((int)strlen(p_fmt)) * 2 + 65536;   // Use a rubric appropriate for your code
  std::string str;
  while (1) {     // Maximum two passes on a POSIX system...
    str.resize(size);
    int n = vsnprintf((char *)str.data(), size, p_fmt, p_args);
    if (n > -1 && n < size) {  // Everything worked
      str.resize(n);
      return str;
    }
    if (n > -1)  // Needed size returned
      size = n + 1;   // For null char
    else
      size *= 2;      // Guess at a larger size (OS specific)
  }

  return str;
}

}
