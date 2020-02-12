#ifndef SCENE_SCENE_NODE_HPP
#define SCENE_SCENE_NODE_HPP

#include <assert.h>
#include <vector>

#include "scene.hpp"
#include "../mesh/mesh.hpp"
#include "../math/math.hpp"
#include "../shading/material.hpp"

namespace Engine {
    class Mesh;
    class Material;

    class SceneNode {
    public:
        Mesh*     m_Mesh;
        Material* m_Material;

        math::vec3 BoxMin = math::vec3(-99999.0f);
        math::vec3 BoxMax = math::vec3( 99999.0f);
    private:
        std::vector<SceneNode*> m_Children;
        SceneNode *m_Parent;

        math::mat4 m_Transform;
        math::mat4 m_PrevTransform;
        math::vec3 m_Position = math::vec3(0.0f);
        math::vec4 m_Rotation; // TODO: replace with quaternions
        math::vec3 m_Scale = math::vec3(1.0f);

        bool m_Dirty;
        unsigned int m_ID;
        static unsigned int CounterID;
    public:
        SceneNode(unsigned int id);
        ~SceneNode();

        // scene node transform
        void SetPosition(math::vec3 position);
        void SetRotation(math::vec4 rotation);
        void SetScale(math::vec3 scale);
        void SetScale(float scale);
        math::vec3 GetLocalPosition();
        math::vec4 GetLocalRotation();
        math::vec3 GetLocalScale();
        math::vec3 GetWorldPosition();
        math::vec3 GetWorldScale();

        unsigned int GetID();
        void AddChild(SceneNode *node);
        void RemoveChild(unsigned int id);
        // TODO: identify children with hash ID
        std::vector<SceneNode*> GetChildren();
        unsigned int            GetChildCount();
        SceneNode              *GetChild(unsigned int id);
        SceneNode              *GetChildByIndex(unsigned int index);
        SceneNode              *GetParent();

        math::mat4 GetTransform();
        math::mat4 GetPrevTransform();

        void UpdateTransform(bool updatePrevTransform = false);
    };
}

#endif //SCENE_SCENE_NODE_HPP