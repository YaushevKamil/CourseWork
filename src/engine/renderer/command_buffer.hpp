#ifndef RENDERER_COMMAND_BUFFER_HPP
#define RENDERER_COMMAND_BUFFER_HPP

#include <map>
#include <vector>

#include "render_command.hpp"
#include "../math/math.hpp"

namespace Engine {
    class Renderer;
    class Mesh;
    class Material;
    class RenderTarget;

    class CommandBuffer {
    private:
        Renderer* m_Renderer;

        std::vector<RenderCommand> m_DeferredRenderCommands;
        std::vector<RenderCommand> m_AlphaRenderCommands;
        std::vector<RenderCommand> m_PostProcessingRenderCommands;
        std::map<RenderTarget*, std::vector<RenderCommand>> m_CustomRenderCommands;

    public:
        CommandBuffer(Renderer* renderer);
        ~CommandBuffer();

        void Push(Mesh* mesh, Material* material, math::mat4 transform = math::mat4(), math::mat4 prevTransform = math::mat4(), math::vec3 boxMin = math::vec3(-99999.0f), math::vec3 boxMax = math::vec3(99999.0f), RenderTarget* target = nullptr);

        void Clear();
        // TODO: build an approach using texture arrays (every push would add relevant material textures
        // to texture array (if it was't there already), and then add a texture index to each material
        // slot; profile if the added texture adjustments actually saves performance!
        void Sort();

        std::vector<RenderCommand> GetDeferredRenderCommands(bool cull = false);
        std::vector<RenderCommand> GetAlphaRenderCommands(bool cull = false);
        std::vector<RenderCommand> GetCustomRenderCommands(RenderTarget *target, bool cull = false);
        std::vector<RenderCommand> GetPostProcessingRenderCommands();
        std::vector<RenderCommand> GetShadowCastRenderCommands();
    };
}


#endif //RENDERER_COMMAND_BUFFER_HPP