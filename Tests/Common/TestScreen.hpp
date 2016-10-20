#pragma once

#include <Engine/Window/Screen.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>
#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/IO/FileHandler.hpp>

using namespace hx3d;

class TestScreen: public Window::Screen {
public:
  TestScreen();

protected:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;

private:
  Graphics::Shader m_shader;
  Utils::File m_file;
};
