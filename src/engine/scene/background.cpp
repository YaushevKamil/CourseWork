#include "background.hpp"

namespace Engine {
    Background::Background() : SceneNode(Scene::CounterID++) {
        Scene::Root->AddChild(this);

        m_Shader = Resources::LoadShader("background", "shaders/background.vs", "shaders/background.fs");
        m_Material = new Engine::Material(m_Shader);
        m_Mesh = new Engine::Cube;
        BoxMin = math::vec3(-99999.0);
        BoxMax = math::vec3( 99999.0);

        m_Material->SetFloat("Exposure", 1.0f);
        m_Material->DepthCompare = GL_LEQUAL;
        m_Material->Cull = false;
        m_Material->ShadowCast = false;
        m_Material->ShadowReceive = false;
    }

    Background::~Background() {}

    void Background::SetCubemap(TextureCube* cubemap) {
        m_CubeMap = cubemap;
        m_Material->SetTextureCube("background", m_CubeMap, 0);
    }
}