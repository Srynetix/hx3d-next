#pragma once

#include <Engine/Core/Types.hpp>

namespace hx3d {

template <class Type>
class RangeType {
public:
  class Iterator: public std::iterator<std::forward_iterator_tag, Type> {
    friend class RangeType;

    public:
      Type operator*() const {
        return m_i;
      }

      const Iterator& operator++() {
        ++m_i;
        return *this;
      }

      Iterator operator++(int) {
        Iterator copy(*this);
        ++m_i;
        return copy;
      }

      bool operator==(const Iterator& p_other) const {
        return m_i == p_other.m_i;
      }

      bool operator!=(const Iterator& p_other) const {
        return m_i != p_other.m_i;
      }

    protected:
      Iterator(Type p_start):
        m_i(p_start)
      {}

    private:
      Type m_i;
  };

  Iterator begin() const {
    return m_begin;
  }

  Iterator end() const {
    return m_end;
  }

  RangeType(Type p_begin, Type p_end):
    m_begin(p_begin), m_end(p_end)
  {}

private:
  Iterator m_begin;
  Iterator m_end;
};

using Range = RangeType<S64>;

}
