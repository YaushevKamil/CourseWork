#ifndef SCENE_BACKGROUND_HPP
#define SCENE_BACKGROUND_HPP

#include "scene_node.hpp"
#include "scene.hpp"
#include "../mesh/cube.hpp"
#include "../renderer/renderer.hpp"

namespace Engine {
    class TextureCube;
    class Material;
    class Shader;
    class Renderer;
    class Cube;

    class Background : public SceneNode {
    private:
        TextureCube* m_CubeMap;
        Shader* m_Shader;

    public:
        Background();
        ~Background();

        void SetCubemap(TextureCube* cubemap);
    };
}

#endif //SCENE_BACKGROUND_HPP
