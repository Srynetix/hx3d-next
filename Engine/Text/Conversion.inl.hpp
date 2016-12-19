namespace hx3d {
namespace Text {

template <class Type>
inline const std::string ToString(const Type& p_value) {
  std::ostringstream oss;
  oss << p_value;
  return oss.str();
}

template <>
inline const std::string ToString(const std::type_index& p_value) {
  return p_value.name();
}

template <>
inline const std::string ToString(const U8& p_value) {
  return ToString((U16)p_value);
}

template <>
inline const std::string ToString(const glm::vec4& p_value) {
  std::ostringstream oss;
  oss << "(" << p_value.x << ", " << p_value.y << ", " << p_value.z << ", " << p_value.w << ")";
  return oss.str();
}

template <>
inline const F32 Convert(const std::string& p_str) {
  return std::stof(p_str);
}

template <>
inline const F64 Convert(const std::string& p_str) {
  return std::stod(p_str);
}

template <>
inline const bool Convert(const std::string& p_str) {
  if (p_str == "False" || p_str == "false") {
    return false;
  }

  if (p_str == "True" || p_str == "true") {
    return true;
  }

  throw Exceptions::BadConversion<std::string, bool>(p_str);
}

template <>
inline const S32 Convert(const std::string& p_str) {
  return std::stoi(p_str);
}

template <>
inline const S64 Convert(const std::string& p_str) {
  return std::stoll(p_str);
}

template <>
inline const U32 Convert(const std::string& p_str) {
  return std::stoul(p_str);
}

template <>
inline const U64 Convert(const std::string& p_str) {
  return std::stoull(p_str);
}

template <>
inline const std::string Convert(const std::string& p_str) {
	return p_str;
}

}
}
