#include <Engine/Utils/Exceptions/BadConversion.hpp>
#include <Engine/Core/Types.hpp>

#include <sstream>

namespace hx3d {
namespace Utils {

template <class Type>
inline const std::string to_string(const Type p_value) {
  std::ostringstream oss;
  oss << p_value;
  return oss.str();
}

template <>
inline const F32 convert(const std::string& p_str) {
  return std::stof(p_str);
}

template <>
inline const F64 convert(const std::string& p_str) {
  return std::stod(p_str);
}

template <>
inline const bool convert(const std::string& p_str) {
  if (p_str == "False" || p_str == "false") {
    return false;
  }

  if (p_str == "True" || p_str == "true") {
    return true;
  }

  throw Exceptions::BadConversion<std::string, bool>(p_str);
}

template <>
inline const S32 convert(const std::string& p_str) {
  return std::stoi(p_str);
}

template <>
inline const S64 convert(const std::string& p_str) {
  return std::stoll(p_str);
}

template <>
inline const U32 convert(const std::string& p_str) {
  return std::stoul(p_str);
}

template <>
inline const U64 convert(const std::string& p_str) {
  return std::stoull(p_str);
}

template <>
inline const std::string convert(const std::string& p_str) {
	return p_str;
}

}
}
