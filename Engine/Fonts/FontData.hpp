#pragma once

#include <Engine/Core/Types.hpp>

namespace hx3d {
namespace Fonts {

struct FontData {
  U32 m_advanceX;
  U32 m_advanceY;

  U32 m_width;
  U32 m_rows;

  S32 m_left;
  S32 m_top;

  F32 m_tx;

  void* m_buffer;

  FontData():
    m_advanceX(0),
    m_advanceY(0),
    m_width(0),
    m_rows(0),
    m_left(0),
    m_top(0),
    m_tx(0.f),
    m_buffer(nullptr)
    {}
};

}
}
