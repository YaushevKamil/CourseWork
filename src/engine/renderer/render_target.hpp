#ifndef RENDERER_RENDER_TARGET_HPP
#define RENDERER_RENDER_TARGET_HPP

#include <vector>

#include "renderer.hpp"
#include "../shading/texture.hpp"
#include "../glad/glad.h"

namespace Engine {
    class RenderTarget {
        friend Renderer;
    public:
        unsigned int ID;

        unsigned int Width;
        unsigned int Height;
        GLenum Type;

        bool HasDepthAndStencil;
    private:
        GLenum m_Target = GL_TEXTURE_2D;
        Texture m_DepthStencil;
        std::vector<Texture> m_ColorAttachments;
    public:
        RenderTarget(unsigned int width, unsigned int height, GLenum type = GL_UNSIGNED_BYTE, unsigned int nrColorAttachments = 1, bool depthAndStencil = true);

        Texture *GetDepthStencilTexture();
        Texture *GetColorTexture(unsigned int index);

        void Resize(unsigned int width, unsigned int height);
        void SetTarget(GLenum target);
    };
}

#endif //RENDERER_RENDER_TARGET_HPP