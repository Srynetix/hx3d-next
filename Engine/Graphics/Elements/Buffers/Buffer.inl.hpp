namespace hx3d {
namespace Graphics {

template <>
inline GLenum GetOpenGLType<F32>() {
  return GL_FLOAT;
}

template <>
inline GLenum GetOpenGLType<U32>() {
  return GL_UNSIGNED_INT;
}

template <>
inline GLenum GetOpenGLType<U16>() {
  return GL_UNSIGNED_SHORT;
}

template <>
inline GLenum GetOpenGLType<F64>() {
  return GL_DOUBLE;
}

}
}
