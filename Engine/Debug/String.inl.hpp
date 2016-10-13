#include <sstream>

namespace hx3d {

template <class Type>
const std::string to_string(const Type p_value) {
  std::ostringstream oss;
  oss << p_value;
  return oss.str();
}

}
