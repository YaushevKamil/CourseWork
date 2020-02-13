#include "resources.hpp"

#include "font_loader.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
#include "mesh_loader.hpp"

#include "../scene/scene.hpp"
#include "../scene/scene_node.hpp"

#include "../utility/string_id.hpp"

#include <vector>

namespace Engine {
    std::map<unsigned int, Font>        Resources::m_Fonts        = std::map<unsigned int, Font>();
    std::map<unsigned int, Shader>      Resources::m_Shaders      = std::map<unsigned int, Shader>();
    std::map<unsigned int, Texture>     Resources::m_Textures     = std::map<unsigned int, Texture>();
    std::map<unsigned int, TextureCube> Resources::m_TexturesCube = std::map<unsigned int, TextureCube>();
    std::map<unsigned int, SceneNode*>  Resources::m_Meshes       = std::map<unsigned int, SceneNode*>();

    void Resources::Init() {
        Texture placeholderTexture;
    }

    void Resources::Clean() {
        for (auto it = m_Meshes.begin(); it != m_Meshes.end(); it++) {
            delete it->second;
        }
    }

    Font* Resources::LoadFont(std::string name, std::string path) {
        unsigned int id = SID(name);

        if (Resources::m_Fonts.find(id) != Resources::m_Fonts.end()) {
            return &Resources::m_Fonts[id];
        }

        Log::Message("Loading font file at: " + path + ".", LOG_INIT);
        Font font = FontLoader::LoadFont(name, path);
        Log::Message(name + " successfully loaded at: " + path + ".", LOG_INIT);

        Resources::m_Fonts[id] = font;
        return &Resources::m_Fonts[id];
    }

    Font* Resources::GetFont(std::string name) {
        unsigned int id = SID(name);

        if (Resources::m_Fonts.find(id) != Resources::m_Fonts.end()) {
            return &Resources::m_Fonts[id];
        } else {
            Log::Message("Requested font: " + name + " not found!", LOG_WARNING);
            return nullptr;
        }
    }

    Shader* Resources::LoadShader(std::string name, std::string vsPath, std::string fsPath, std::vector<std::string> defines) {
        unsigned int id = SID(name);

        if (Resources::m_Shaders.find(id) != Resources::m_Shaders.end()) {
            return &Resources::m_Shaders[id];
        }

        Log::Message("Loading shader: " + name + "at: " + vsPath + ", " + fsPath + ".", LOG_INIT);
        Shader shader = ShaderLoader::Load(name, vsPath, fsPath, defines);
        Log::Message(name + " successfully loaded at: " + vsPath + ", " + fsPath + ".", LOG_INIT);

        Resources::m_Shaders[id] = shader;
        return &Resources::m_Shaders[id];
    }

    Shader* Resources::GetShader(std::string name) {
        unsigned int id = SID(name);

        if (Resources::m_Shaders.find(id) != Resources::m_Shaders.end()) {
            return &Resources::m_Shaders[id];
        } else {
            Log::Message("Requested shader: " + name + " not found!", LOG_WARNING);
            return nullptr;
        }
    }

    Texture* Resources::LoadTexture(std::string name, std::string path, GLenum target, GLenum format, bool srgb) {
        unsigned int id = SID(name);

        if (Resources::m_Textures.find(id) != Resources::m_Textures.end()) {
            return &Resources::m_Textures[id];
        }

        Log::Message("Loading texture file at: " + path + ".", LOG_INIT);
        Texture texture = TextureLoader::LoadTexture(path, target, format, srgb);
        Log::Message("Successfully loaded: " + path + ".", LOG_INIT);

        if (texture.Width > 0) {
            Resources::m_Textures[id] = texture;
            return &Resources::m_Textures[id];
        } else {
            return nullptr;
        }
    }

    Texture* Resources::LoadHDR(std::string name, std::string path) {
        unsigned int id = SID(name);

        if (Resources::m_Textures.find(id) != Resources::m_Textures.end()) {
            return &Resources::m_Textures[id];
        }

        Log::Message("Loading HDR texture file at: " + path + ".", LOG_INIT);

        Texture texture = TextureLoader::LoadHDRTexture(path);
        if (texture.Width > 0) {
            Resources::m_Textures[id] = texture;
            Log::Message("Successfully loaded: " + path + ".", LOG_INIT);
            return &Resources::m_Textures[id];
        } else {
            Log::Message("Requested HDR texture: " + name + " not found!", LOG_WARNING);
            return nullptr;
        }
    }

    Texture* Resources::GetTexture(std::string name) {
        unsigned int id = SID(name);

        if (Resources::m_Textures.find(id) != Resources::m_Textures.end()) {
            return &Resources::m_Textures[id];
        } else {
            Log::Message("Requested texture: " + name + " not found!", LOG_WARNING);
            return nullptr;
        }
    }

    TextureCube* Resources::LoadTextureCube(std::string name, std::string folder) {
        unsigned int id = SID(name);

        if (Resources::m_TexturesCube.find(id) != Resources::m_TexturesCube.end()) {
            return &Resources::m_TexturesCube[id];
        }

        TextureCube texture = TextureLoader::LoadTextureCube(folder);
        Resources::m_TexturesCube[id] = texture;
        return &Resources::m_TexturesCube[id];
    }

    TextureCube* Resources::GetTextureCube(std::string name) {
        unsigned int id = SID(name);

        if (Resources::m_TexturesCube.find(id) != Resources::m_TexturesCube.end()) {
            return &Resources::m_TexturesCube[id];
        } else {
            Log::Message("Requested texture cube: " + name + " not found!", LOG_WARNING);
            return nullptr;
        }
    }

    SceneNode* Resources::LoadMesh(Renderer* renderer, std::string name, std::string path) {
        unsigned int id = SID(name);

        if (Resources::m_Meshes.find(id) != Resources::m_Meshes.end()) {
            return Scene::MakeSceneNode(Resources::m_Meshes[id]);
        }

        SceneNode* node = MeshLoader::LoadMesh(renderer, path);
        Resources::m_Meshes[id] = node;

        return Scene::MakeSceneNode(node);
    }

    SceneNode* Resources::GetMesh(std::string name) {
        unsigned int id = SID(name);

        if (Resources::m_Meshes.find(id) != Resources::m_Meshes.end()) {
            return Scene::MakeSceneNode(Resources::m_Meshes[id]);
        } else {
            Log::Message("Requested mesh: " + name + " not found!", LOG_WARNING);
            return nullptr;
        }
    }
}