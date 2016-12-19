#pragma once

#include <string>
#include <map>
#include <cassert>

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>

namespace hx3d {
namespace Utils {

template <class ResourceType>
class ResourceManager {
public:
  ResourceManager() {
    HX3D_LOGGER(kResources).debug("Resource Manager for {} created at address {}", GetTypename<ResourceManager>(), this);
  }

  void loadFromFile(const std::string& p_name, const std::string& p_pathToFile) {
    auto pos = m_resources.find(p_name);
    assert(pos == m_resources.end());

    ResourceType& resource = m_resources[p_name];
    resource.loadFromFile(p_pathToFile);

    HX3D_LOGGER(kResources).debug("Resource type {} loaded: {} ({})", GetTypename<ResourceType>(), p_name, p_pathToFile);
  }

  void loadFromFile(const std::string& p_name, Utils::File&& p_file) {
    auto pos = m_resources.find(p_name);
    assert(pos == m_resources.end());

    ResourceType& resource = m_resources[p_name];
    resource.loadFromFile(std::move(p_file));

    HX3D_LOGGER(kResources).debug("Resource type {} loaded: {} (memfile)", GetTypename<ResourceType>(), p_name);
  }

  ResourceType& get(const std::string& p_name) {
    auto pos = m_resources.find(p_name);
    if (pos == m_resources.end()) {
      throw Exceptions::KeyNotFound<ResourceManager, std::string>(p_name);
    }

    return m_resources[p_name];
  }

private:
  std::map<std::string, ResourceType> m_resources;
};

}
}
