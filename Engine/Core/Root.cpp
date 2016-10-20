#include <Engine/Core/Root.hpp>
#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Debug/Logging.hpp>

namespace hx3d {

EngineRoot::EngineRoot() {}

EngineRoot::~EngineRoot() {
  SFileLoader::Release();
}

void EngineRoot::Start() {
  const auto& core_logger = HX3D_LOGGER(kCore);
  SFileLoader::Initialize();

  // Loading config
  core_logger.info("Loading engine configuration...");
  m_engineConfigHandler.parseFromFile("EngineConfig.ini");

  core_logger.info("Engine Root ready !");
}

Utils::FileLoader& EngineRoot::getFileLoader() {
  return SFileLoader::Instance();
}

const Utils::INIHandler& EngineRoot::getEngineConfiguration() const {
  return m_engineConfigHandler;
}

}
