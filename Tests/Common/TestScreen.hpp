#pragma once

#include <Engine/Window/Screen.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>

using namespace hx3d;

class TestScreen: public Window::Screen {
private:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;

private:
  Graphics::Shader m_shader;
};
