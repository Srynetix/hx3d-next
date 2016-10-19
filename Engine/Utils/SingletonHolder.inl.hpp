namespace hx3d {
namespace Utils {

template <class Type>
Type* SingletonHolder<Type>::p_instance = nullptr;

template <class Type>
Type& SingletonHolder<Type>::Instance() {
  if (!p_instance) {
    p_instance = new Type();
  }

  return *p_instance;
}

template <class Type>
void SingletonHolder<Type>::Release() {
  if (p_instance) {
    delete p_instance;
  }

  p_instance = nullptr;
}

}
}
