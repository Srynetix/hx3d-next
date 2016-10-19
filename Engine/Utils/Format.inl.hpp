#include <regex>

#include <Engine/Core/Types.hpp>
#include <Engine/Utils/Conversion.hpp>

namespace hx3d {
namespace Utils {

template <class... Args, class Current>
std::string sformat_(const std::string& p_str, const Current& p_val, const std::regex& p_rgx, Args&&... args) {
  std::smatch matches;
  std::string next_str(p_str);

  std::regex_search(p_str, matches, p_rgx);
  if (matches.size() > 0) {
    const auto& str = matches[0].str();
    const size_t pos = matches.position(0);
    const size_t next = pos + str.size();

    std::string prev_str = p_str.substr(0, pos);
    return prev_str + to_string(p_val) + sformat(p_str.substr(next, p_str.size()), args...);
  }

  else {
    return sformat(p_str, args...);
  }
}

template <class... Args, class T>
inline std::string sformat(const std::string& p_str, T* p_ptr, Args&&... args) {
  return sformat_(p_str, p_ptr, std::regex("%p"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const F32 p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%f"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const F64 p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%lf"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const U32 p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%u"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const U64 p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%lu"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const S32 p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%d"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const S64 p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%ld"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const char* p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%s"), args...);
}

template <class... Args>
inline std::string sformat(const std::string& p_str, const std::string& p_val, Args&&... args) {
  return sformat_(p_str, p_val, std::regex("%s"), args...);
}

inline std::string sformat(const std::string& p_str) {
  return p_str;
}

}
}
