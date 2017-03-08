#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Math/Transform.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>

#include <vector>

namespace hx3d {
namespace Game {

class Tree;
class Node {
public:
  Node(): m_parent(nullptr) {}
  Node(Node* p_parent): m_parent(p_parent) {}

  template <class T>
  void createChild() {
    auto child = Utils::MakeUniquePtr<T>();
    child->m_parent = this;
    m_children.push_back(std::move(child));
  }

  friend class Tree;

private:
  Node* m_parent;
  std::vector<Utils::UniquePtr<Node>> m_children;
};

class Tree {
public:
  Tree() {}

  inline Node& getRoot() {
    return m_root;
  }

private:
  Node m_root;
};

class SceneNode: public Node {
public:
  virtual void update(const F32 p_delta) = 0;
  virtual void draw(Graphics::Shader& p_shader) = 0;

  inline Math::Transform& getTransform() { return m_transform; }

private:
  Math::Transform m_transform;
};

class TestSceneNode: public SceneNode {
public:
  virtual void update(const F32 p_delta) {}
  virtual void draw(Graphics::Shader& p_shader) {}
};

class SceneGraph: public Tree {
};

}
}
