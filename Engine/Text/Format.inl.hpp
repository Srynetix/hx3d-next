namespace hx3d {
namespace Text {

template <class... Args, class Current>
std::string Format_(const std::string& p_str, const Current& p_val, const std::regex& p_rgx, Args&&... p_args) {
  std::smatch matches;
  std::string next_str(p_str);

  std::regex_search(p_str, matches, p_rgx);
  if (matches.size() > 0) {
    const auto& str = matches[0].str();
    const size_t pos = matches.position(0);
    const size_t next = pos + str.size();

    std::string prev_str = p_str.substr(0, pos);
    return prev_str + ToString(p_val) + Format(p_str.substr(next, p_str.size()), p_args...);
  }

  else {
    return Format(p_str, p_args...);
  }
}

template <class... Args, class Current>
inline std::string Format(const std::string& p_str, const Current& p_current, Args&&... p_args) {
  return Format_(p_str, p_current, std::regex("\\{\\}"), p_args...);
}

template <class... Args, class T>
inline std::string Format(const std::string& p_str, T* p_ptr, Args&&... p_args) {
  return Format_(p_str, p_ptr, std::regex("(%p|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const F32 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%(f|lf)|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const F64 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%lf|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const U32 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%(u|lu)|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const U64 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%lu|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const S32 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%(d|ld)|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const S64 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%ld|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const U8 p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%(u|lu)|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const char* p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%s|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, unsigned char* p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%s|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const unsigned char* p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%s|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, char* p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%s|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const std::string& p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%s|\\{\\})"), p_args...);
}

template <class... Args>
inline std::string Format(const std::string& p_str, const glm::vec4& p_val, Args&&... p_args) {
  return Format_(p_str, p_val, std::regex("(%v|\\{\\})"), p_args...);
}

inline std::string Format(const std::string& p_str) {
  return p_str;
}

}
}
