#pragma once

#include <string>
#include <map>
#include <cassert>

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/Uncopyable.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>

namespace hx3d {
namespace Utils {

template <class ResourceType>
class ResourceManager: public Utils::Uncopyable {
public:
  ResourceManager() {
    HX3D_LOGGER(kResources).debug("Resource Manager for {} created at address {}", GetTypename<ResourceManager>(), this);
  }

  const Utils::SharedPtr<ResourceType>& loadFromFile(const std::string& p_name, const std::string& p_pathToFile) {
    auto pos = m_resources.find(p_name);
    assert(pos == m_resources.end());

    auto resource = Utils::MakeSharedPtr<ResourceType>();
    resource->loadFromFile(p_pathToFile);

    m_resources[p_name] = resource;
    HX3D_LOGGER(kResources).debug("Resource type {} loaded: {} ({})", GetTypename<ResourceType>(), p_name, p_pathToFile);

    return m_resources[p_name];
  }

  const Utils::SharedPtr<ResourceType>& loadFromFile(const std::string& p_name, Utils::File&& p_file) {
    auto pos = m_resources.find(p_name);
    assert(pos == m_resources.end());

    auto resource = Utils::MakeSharedPtr<ResourceType>();
    resource->loadFromFile(std::move(p_file));

    m_resources[p_name] = resource;
    HX3D_LOGGER(kResources).debug("Resource type {} loaded: {} (memfile)", GetTypename<ResourceType>(), p_name);

    return m_resources[p_name];
  }

  ResourceType& get(const std::string& p_name) {
    auto pos = m_resources.find(p_name);
    if (pos == m_resources.end()) {
      throw Exceptions::KeyNotFound<ResourceManager, std::string>(p_name);
    }

    return *(m_resources[p_name].get());
  }

  const SharedPtr<ResourceType>& getShared(const std::string& p_name) {
    auto pos = m_resources.find(p_name);
    if (pos == m_resources.end()) {
      throw Exceptions::KeyNotFound<ResourceManager, std::string>(p_name);
    }

    return m_resources[p_name];
  }

private:
  std::map<std::string, SharedPtr<ResourceType>> m_resources;
};

}
}
