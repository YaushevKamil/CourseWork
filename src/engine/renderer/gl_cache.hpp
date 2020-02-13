#ifndef RENDERER_GL_CACHE_HPP
#define RENDERER_GL_CACHE_HPP

#include "../glad/glad.h"

namespace Engine {
    class GLCache {
    private:
        bool m_DepthTest;
        bool m_Blend;
        bool m_CullFace;

        GLenum m_DepthFunc;
        GLenum m_BlendSrc;
        GLenum m_BlendDst;
        GLenum m_FrontFace;
        GLenum m_PolygonMode;

        unsigned int m_ActiveShaderID;
    public:
        GLCache();
        ~GLCache();

        void SetDepthTest(bool enable);
        void SetDepthFunc(GLenum depthFunc);
        void SetBlend(bool enable);
        void SetBlendFunc(GLenum src, GLenum dst);
        void SetCull(bool enable);
        void SetCullFace(GLenum face);
        void SetPolygonMode(GLenum mode);

        void SwitchShader(unsigned int ID);
    };
}

#endif //RENDERER_GL_CACHE_HPP