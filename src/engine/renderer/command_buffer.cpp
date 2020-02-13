#include <algorithm>
#include <tuple>

#include "command_buffer.hpp"
#include "renderer.hpp"
#include "../camera/camera.hpp"
#include "../shading/material.hpp"
#include "../mesh/mesh.hpp"

namespace Engine {
    CommandBuffer::CommandBuffer(Renderer* renderer) {
        m_Renderer = renderer;
    }

    CommandBuffer::~CommandBuffer() {
        Clear();
    }

    void CommandBuffer::Push(Mesh* mesh, Material* material, math::mat4 transform, math::mat4 prevTransform, math::vec3 boxMin, math::vec3 boxMax, RenderTarget* target) {
        RenderCommand command = {};
        command.c_Mesh          = mesh;
        command.c_Material      = material;
        command.c_Transform     = transform;
        command.c_PrevTransform = prevTransform;
        command.c_BoxMin        = boxMin;
        command.c_BoxMax        = boxMax;

        if (material->Blend) {
            material->Type = MATERIAL_CUSTOM;
            m_AlphaRenderCommands.push_back(command);
        } else {
            if (material->Type == MATERIAL_DEFAULT) {
                m_DeferredRenderCommands.push_back(command);
            } else if (material->Type == MATERIAL_CUSTOM) {
                if (m_CustomRenderCommands.find(target) != m_CustomRenderCommands.end()) {
                    m_CustomRenderCommands[target].push_back(command);
                } else {
                    m_CustomRenderCommands[target] = std::vector<RenderCommand>();
                    m_CustomRenderCommands[target].push_back(command);
                }
            } else if (material->Type == MATERIAL_POST_PROCESS) {
                m_PostProcessingRenderCommands.push_back(command);
            }
        }
    }

    void CommandBuffer::Clear() {
        m_DeferredRenderCommands.clear();
        m_CustomRenderCommands.clear();
        m_PostProcessingRenderCommands.clear();
        m_AlphaRenderCommands.clear();
    }

    bool renderSortDeferred(const RenderCommand &a, const RenderCommand &b) {
        return a.c_Material->GetShader()->ID < b.c_Material->GetShader()->ID;
    }

    bool renderSortCustom(const RenderCommand &a, const RenderCommand &b) {
        return std::make_tuple(a.c_Material->Blend, a.c_Material->GetShader()->ID) <
               std::make_tuple(b.c_Material->Blend, b.c_Material->GetShader()->ID);
    }
    bool renderSortShader(const RenderCommand &a, const RenderCommand &b) {
        return a.c_Material->GetShader()->ID < b.c_Material->GetShader()->ID;
    }

    void CommandBuffer::Sort() {
        std::sort(m_DeferredRenderCommands.begin(), m_DeferredRenderCommands.end(), renderSortDeferred);
        for (auto rtIt = m_CustomRenderCommands.begin(); rtIt != m_CustomRenderCommands.end(); rtIt++) {
            std::sort(rtIt->second.begin(), rtIt->second.end(), renderSortCustom);
        }
    }

    std::vector<RenderCommand> CommandBuffer::GetDeferredRenderCommands(bool cull) {
        if (cull) {
            std::vector<RenderCommand> commands;
            for (auto it = m_DeferredRenderCommands.begin(); it != m_DeferredRenderCommands.end(); ++it) {
                RenderCommand command = *it;
                if (m_Renderer->GetCamera()->Frustum.Intersect(command.c_BoxMin, command.c_BoxMax)) {
                    commands.push_back(command);
                }
            }
            return commands;
        } else {
            return m_DeferredRenderCommands;
        }
    }

    std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget *target, bool cull) {
        if (target == nullptr && cull) {
            std::vector<RenderCommand> commands;
            for (auto it = m_CustomRenderCommands[target].begin(); it != m_CustomRenderCommands[target].end(); ++it) {
                RenderCommand command = *it;
                if (m_Renderer->GetCamera()->Frustum.Intersect(command.c_BoxMin, command.c_BoxMax)) {
                    commands.push_back(command);
                }
            }
            return commands;
        } else {
            return m_CustomRenderCommands[target];
        }
    }

    std::vector<RenderCommand> CommandBuffer::GetAlphaRenderCommands(bool cull) {
        if (cull) {
            std::vector<RenderCommand> commands;
            for (auto it = m_AlphaRenderCommands.begin(); it != m_AlphaRenderCommands.end(); ++it) {
                RenderCommand command = *it;
                if (m_Renderer->GetCamera()->Frustum.Intersect(command.c_BoxMin, command.c_BoxMax)) {
                    commands.push_back(command);
                }
            }
            return commands;
        } else {
            return m_AlphaRenderCommands;
        }
    }

    std::vector<RenderCommand> CommandBuffer::GetPostProcessingRenderCommands() {
        return m_PostProcessingRenderCommands;
    }

    std::vector<RenderCommand> CommandBuffer::GetShadowCastRenderCommands() {
        std::vector<RenderCommand> commands;
        for (auto it = m_DeferredRenderCommands.begin(); it != m_DeferredRenderCommands.end(); ++it) {
            if (it->c_Material->ShadowCast) {
                commands.push_back(*it);
            }
        }
        for (auto it = m_CustomRenderCommands[nullptr].begin(); it != m_CustomRenderCommands[nullptr].end(); ++it) {
            if (it->c_Material->ShadowCast) {
                commands.push_back(*it);
            }
        }
        return commands;
    }
};