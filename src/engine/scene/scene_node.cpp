#include "scene_node.hpp"

namespace Engine {
    SceneNode::SceneNode(unsigned int id) :
        m_Mesh(nullptr),
        m_Material(nullptr),
        m_Parent(nullptr),
        m_Dirty(true),
        m_ID(id) {}

    SceneNode::~SceneNode() {
        for (unsigned int i = 0; i < m_Children.size(); ++i) {
            delete m_Children[i];
        }
    }

    void SceneNode::SetPosition(math::vec3 position) {
        m_Position = position;
        m_Dirty = true;
    }

    void SceneNode::SetRotation(math::vec4 rotation) {
        m_Rotation = rotation;
        m_Dirty = true;
        //UpdateTransform();
    }

    void SceneNode::SetScale(math::vec3 scale) {
        m_Scale = scale;
        m_Dirty = true;
    }

    void SceneNode::SetScale(float scale) {
        m_Scale = math::vec3(scale);
        m_Dirty = true;
    }

    math::vec3 SceneNode::GetLocalPosition() {
        return m_Position;
    }

    math::vec4 SceneNode::GetLocalRotation() {
        return m_Rotation;
    }

    math::vec3 SceneNode::GetLocalScale() {
        return m_Scale;
    }

    math::vec3 SceneNode::GetWorldPosition() {
        math::mat4 transform = GetTransform();
        math::vec4 position = math::vec4(m_Position, 1.0f);
        math::vec4 pos = transform * position;
        return pos.xyz;
    }

    math::vec3 SceneNode::GetWorldScale() {
        math::mat4 transform = GetTransform();
        math::vec3 scale = math::vec3(transform[0][0], transform[1][1], transform[2][2]);
        if (scale.x < 0.0f) scale.x *= -1.0f;
        if (scale.y < 0.0f) scale.y *= -1.0f;
        if (scale.z < 0.0f) scale.z *= -1.0f;
        return scale;
    }

    unsigned int SceneNode::GetID() {
        return m_ID;
    }

    void SceneNode::AddChild(SceneNode *node) {
        if (node->m_Parent) {
            node->m_Parent->RemoveChild(node->m_ID);
        }
        node->m_Parent = this;
        m_Children.push_back(node);
    }

    void SceneNode::RemoveChild(unsigned int id) {
        auto it = std::find(m_Children.begin(), m_Children.end(), GetChild(id));
        if (it != m_Children.end())
            m_Children.erase(it);
    }

    std::vector<SceneNode*> SceneNode::GetChildren() {
        return m_Children;
    }

    unsigned int SceneNode::GetChildCount() {
        return m_Children.size();
    }

    SceneNode *SceneNode::GetChild(unsigned int id) {
        for (unsigned int i = 0; i < m_Children.size(); ++i) {
            if (m_Children[i]->GetID() == id)
                return m_Children[i];
        }
        return nullptr;
    }

    SceneNode* SceneNode::GetChildByIndex(unsigned int index) {
        assert(index < GetChildCount());
        return m_Children[index];
    }

    SceneNode *SceneNode::GetParent() {
        return m_Parent;
    }

    math::mat4 SceneNode::GetTransform() {
        if (m_Dirty) {
            UpdateTransform(false);
        }
        return m_Transform;
    }

    math::mat4 SceneNode::GetPrevTransform() {
        return m_PrevTransform;
    }

    void SceneNode::UpdateTransform(bool updatePrevTransform) {
        if (updatePrevTransform) {
            m_PrevTransform = m_Transform;
        }
        if (m_Dirty) {
            m_Transform = math::translate(m_Position);
            m_Transform = math::scale(m_Transform, m_Scale);
            m_Transform = math::rotate(m_Transform, m_Rotation.xyz, m_Rotation.w);
            if (m_Parent) {
                m_Transform = m_Parent->m_Transform * m_Transform;
            }
        }
        for (int i = 0; i < m_Children.size(); ++i) {
            if (m_Dirty) {
                m_Children[i]->m_Dirty = true;
            }
            m_Children[i]->UpdateTransform(updatePrevTransform);
        }
        m_Dirty = false;
    }
}