#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include "../math/math.hpp"

#include "../lighting/point_light.hpp"
#include "../lighting/directional_light.hpp"
#include "../mesh/quad.hpp"
#include "command_buffer.hpp"
#include "pbr_capture.hpp"
#include "gl_cache.hpp"

#include "../glad/glad.h"

namespace Engine {
    class Mesh;
    class Material;
    class SceneNode;
    class Camera;
    class RenderTarget;
    class MaterialLibrary;
    class PBR;
    class PostProcessor;

    class Renderer {
        friend PostProcessor;
        friend PBR;
    public:
        bool IrradianceGI = true;
        bool Shadows      = true;
        bool Lights       = true;
        bool RenderLights = true;
        bool LightVolumes = false;
        bool RenderProbes = false;
        bool Wireframe    = false;
    private:
        CommandBuffer* m_CommandBuffer;
        GLCache        m_GLCache/* = GLCache()*/;
        math::vec2     m_RenderSize;

        std::vector<DirectionalLight*> m_DirectionalLights;
        std::vector<PointLight*>       m_PointLights;
        RenderTarget* m_GBuffer = nullptr;
        Mesh*         m_DeferredPointMesh;

        MaterialLibrary* m_MaterialLibrary;

        Camera*    m_Camera;
        math::mat4 m_PrevViewProjection;

        std::vector<RenderTarget*> m_RenderTargetsCustom;
        RenderTarget*              m_CurrentRenderTargetCustom = nullptr;
        RenderTarget*              m_CustomTarget;
        RenderTarget*              m_PostProcessTarget1;
        PostProcessor*             m_PostProcessor;
        Quad*                      m_NDCPlane;
        unsigned int m_FramebufferCubemap;
        unsigned int m_CubemapDepthRBO;

        std::vector<RenderTarget*> m_ShadowRenderTargets;
        std::vector<math::mat4>    m_ShadowViewProjections;

        PBR* m_PBR;
        unsigned int m_PBREnvironmentIndex;
        std::vector<math::vec4> m_ProbeSpatials;

        unsigned int m_GlobalUBO;

        Mesh* m_DebugLightMesh;

    public:
        Renderer();
        ~Renderer();

        void Init(GLADloadproc loadProcFunc);

        void SetRenderSize(unsigned int width, unsigned int height);
        math::vec2 GetRenderSize();

        void SetTarget(RenderTarget* renderTarget, GLenum target = GL_TEXTURE_2D);

        Camera* GetCamera();
        void    SetCamera(Camera* camera);

        PostProcessor* GetPostProcessor();


        Material* CreateMaterial(std::string base = "default");
        Material* CreateCustomMaterial(Shader* shader);
        Material* CreatePostProcessingMaterial(Shader* shader);

        void PushRender(Mesh* mesh, Material* material, math::mat4 transform = math::mat4(), math::mat4 prevFrameTransform = math::mat4());
        void PushRender(SceneNode* node);
        void PushPostProcessor(Material* postProcessor);

        void AddLight(DirectionalLight *light);
        void AddLight(PointLight       *light);

        void RenderPushedCommands();

        void Blit(Texture* src, RenderTarget* dst = nullptr, Material* material = nullptr, std::string textureUniformName = "TexSrc");

        void        SetSkyCapture(PBRCapture* pbrEnvironment);
        PBRCapture* GetSkypCature();
        void        AddIrradianceProbe(math::vec3 position, float radius);
        void        BakeProbes(SceneNode* scene = nullptr);
    private:
        void renderCustomCommand(RenderCommand* command, Camera* customCamera, bool updateGLSettings = true);
        void renderToCubemap(SceneNode* scene, TextureCube* target, math::vec3 position = math::vec3(0.0f), unsigned int mipLevel = 0);
        void renderToCubemap(std::vector<RenderCommand>& renderCommands, TextureCube* target, math::vec3 position = math::vec3(0.0f), unsigned int mipLevel = 0);
        static void renderMesh(Mesh* mesh, Shader* shader);

        void updateGlobalUBOs();

        RenderTarget* getCurrentRenderTarget();

        void renderDeferredAmbient();
        void renderDeferredDirLight(DirectionalLight* light);
        void renderDeferredPointLight(PointLight* light);

        void renderShadowCastCommand(RenderCommand* command, const math::mat4& projection, const math::mat4& view);
    };
}


#endif //RENDERER_RENDERER_HPP