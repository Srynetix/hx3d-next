#pragma once

#include <Engine/Utils/SingletonHolder.hpp>
#include <Engine/Utils/Parsers/INIHandler.hpp>

namespace hx3d {

namespace Utils {
  class FileLoader;
}

class EngineRoot {
public:
  EngineRoot();
  ~EngineRoot();

  void Start();

  Utils::FileLoader& getFileLoader();
  const Utils::INIHandler& getEngineConfiguration() const;

private:
  typedef Utils::SingletonHolder<Utils::FileLoader> SFileLoader;

  Utils::INIHandler m_engineConfigHandler;
};

typedef Utils::SingletonHolder<EngineRoot> Root;

}
