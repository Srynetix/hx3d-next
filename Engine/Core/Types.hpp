#pragma once

#include <cstdint>
#include <cfloat>
#include <typeinfo>

namespace hx3d {

typedef uint8_t   U8;    // Max 255
typedef uint16_t  U16;   // Max 65,535
typedef uint32_t  U32;   // Max 4,294,967,295
typedef uint64_t  U64;   // Max 18,446,744,073,709,551,615

typedef int8_t    S8;
typedef int16_t   S16;
typedef int32_t   S32;
typedef int64_t   S64;

typedef float     F32;
typedef double    F64;

template <class Type>
const char* getTypeName() {
  const std::type_info& type = typeid(Type);
  return type.name();
}

template <class Type>
const char* getTypeName(const Type& t) {
  const std::type_info& type = typeid(t);
  return type.name();
}

}
