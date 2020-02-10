#ifndef SHADING_TEXTURE_HPP
#define SHADING_TEXTURE_HPP

#include <assert.h>

#include "../glad/glad.h"

namespace Engine {
    class Texture {
    public:
        unsigned int ID;
        // TODO: implement getters/setters!
        GLenum Target         = GL_TEXTURE_2D;
        GLenum InternalFormat = GL_RGBA;
        GLenum Format         = GL_RGBA;
        GLenum Type           = GL_UNSIGNED_BYTE;
        GLenum FilterMin      = GL_LINEAR_MIPMAP_LINEAR;
        GLenum FilterMax      = GL_LINEAR;
        GLenum WrapS          = GL_REPEAT;
        GLenum WrapT          = GL_REPEAT;
        GLenum WrapR          = GL_REPEAT;
        bool Mipmapping       = true;

        unsigned int Width  = 0;
        unsigned int Height = 0;
        unsigned int Depth  = 0;
    private:
    public:
        Texture();
        ~Texture();

        // 1D texture generation
        void Generate(unsigned int width, GLenum internalFormat, GLenum format, GLenum type, void* data);
        // 2D texture generation
        void Generate(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, void* data);
        // 3D texture generation
        void Generate(unsigned int width, unsigned int height, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, void* data);

        void Resize(unsigned int width, unsigned int height = 0, unsigned int depth = 0);

        void Bind(int unit = -1);
        void Unbind();

        void SetWrapMode(GLenum wrapMode, bool bind = false);
        void SetFilterMin(GLenum filter, bool bind = false);
        void SetFilterMax(GLenum filter, bool bind = false);
    };
}

#endif //SHADING_TEXTURE_HPP