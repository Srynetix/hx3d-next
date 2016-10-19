#include <Tests/Common/TestScreen.hpp>
#include <Engine/Debug/Logging.hpp>

void TestScreen::onCreate() {
  const auto& logger = HX3D_LOGGER(kTests);
  logger.info("Create !");

  m_shader.loadShader("Shaders/BaseNoTexture");
}

void TestScreen::onUpdate(const F32 p_delta) {
}
