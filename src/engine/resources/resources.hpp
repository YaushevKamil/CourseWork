#ifndef RESOURCES_RESOURCES_HPP
#define RESOURCES_RESOURCES_HPP

#include <map>
#include <string>

#include "../shading/font.hpp"
#include "../shading/shader.hpp"
#include "../shading/material.hpp"
#include "../shading/texture.hpp"
#include "../shading/texture_cube.hpp"
#include "../mesh/mesh.hpp"

namespace Engine {
    class SceneNode;
    class Renderer;

    class Resources {
    private:
        static std::map<unsigned int, Shader>      m_Shaders;
        static std::map<unsigned int, Texture>     m_Textures;
        static std::map<unsigned int, TextureCube> m_TexturesCube;
        static std::map<unsigned int, SceneNode*>  m_Meshes;
        static std::map<unsigned int, Font>        m_Fonts;
//        static MapLoader                           m_MapLoader;
    public:

    private:
        Resources();
    public:
        static void Init();
        static void Clean();

        static Shader*      LoadShader(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines = std::vector<std::string>());
        static Shader*      GetShader(std::string name);

        static Texture*     LoadTexture(std::string name, std::string path, GLenum target = GL_TEXTURE_2D, GLenum format = GL_RGBA, bool srgb = false);
        static Texture*     LoadHDR(std::string name, std::string path);
        static TextureCube* LoadTextureCube(std::string name, std::string folder);
        static Texture*     GetTexture(std::string name);
        static TextureCube* GetTextureCube(std::string name);

        static SceneNode*  LoadMesh(Renderer* renderer, std::string name, std::string path);
        static SceneNode*  GetMesh(std::string name);

        static Font* LoadFont(std::string name, std::string path);
        static Font* GetFont(std::string name);
    };
}

#endif //RESOURCES_RESOURCES_HPP