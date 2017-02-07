#pragma once

#include <algorithm>
#include <numeric>

#include <Engine/Utils/Algorithms/Range.hpp>

namespace hx3d {

template <class Collection, class Operation>
void apply(Collection& p_collection, Operation p_operation) {
  std::for_each(p_collection.begin(), p_collection.end(), p_operation);
}

template <class Collection, class Type, class Operation>
Type reduce(const Collection& p_collection, Type p_initialValue, Operation p_operation) {
  return std::accumulate(p_collection.begin(), p_collection.end(), p_initialValue, p_operation);
}

template <class Collection, class Operation>
Collection map(const Collection& p_collection, Operation p_operation) {
  Collection result = p_collection;
  std::transform(p_collection.begin(), p_collection.end(), result.begin(), p_operation);
  return collection;
}

template <class Collection, class Operation>
Collection zip(const Collection& p_firstCollection, const Collection& p_secondCollection, Operation p_operation) {
  Collection result = p_firstCollection;
  std::transform(p_firstCollection.begin(), p_firstCollection.end(), p_secondCollection.begin(), result.begin(), p_operation);
  return result;
}

template <class Collection, class Condition>
bool exists(const Collection& p_collection, Condition p_condition) {
  return std::find_if(p_collection.begin(), p_collection.end(), p_condition) != p_collection.end();
}

template <class Collection, class Condition>
Collection filter_n(const Collection& p_collection, Condition p_condition) {
  Collection result = p_collection;
  auto pos = std::remove_if(result.begin(), result.end(), p_condition);
  result.erase(pos, std::end(result));
  return result;
}

template <class Collection, class Condition>
Collection filter(const Collection& p_collection, Condition p_condition) {
  return filter_n(p_collection, [p_condition](typename Collection::value_type type) {
    return !p_condition(type);
  });
}

}
