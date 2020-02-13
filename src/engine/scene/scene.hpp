#ifndef SCENE_SCENE_HPP
#define SCENE_SCENE_HPP

#include <vector>
#include <stack>

#include "scene_node.hpp"
#include "../shading/material.hpp"

namespace Engine {
    class Mesh;
    class Material;
    class SceneNode;

    class Scene {
    public:
        static SceneNode* Root;
        static unsigned int CounterID;
    public:
        static void Clear();
        static SceneNode* MakeSceneNode();
        static SceneNode* MakeSceneNode(Mesh* mesh, Material* material);
        static SceneNode* MakeSceneNode(SceneNode* node);
        static void DeleteSceneNode(SceneNode* node);
    };
}

#endif //SCENE_SCENE_HPP