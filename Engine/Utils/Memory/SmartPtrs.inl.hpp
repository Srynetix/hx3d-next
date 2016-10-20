namespace hx3d {
namespace Utils {

template <class Type, class... Args>
std::unique_ptr<Type> MakeUniquePtr(Args&&... args) {
  return std::unique_ptr<Type>(new Type(args...));
}

}
}
