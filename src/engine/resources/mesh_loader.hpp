#ifndef RESOURCES_MESH_LOADER_HPP
#define RESOURCES_MESH_LOADER_HPP

#include <string>
#include <vector>

#include "../math/math.hpp"

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
struct aiString;

namespace Engine {
    class Renderer;
    class SceneNode;
    class Mesh;
    class Material;

    class MeshLoader {
    private:
        static std::vector<Mesh*> meshStore;
    public:
        static void       Clean();
        static SceneNode* LoadMesh(Renderer* renderer, std::string path, bool setDefaultMaterial = true);
    private:
        static SceneNode* processNode(Renderer* renderer, aiNode* aNode, const aiScene* aScene, std::string directory, bool setDefaultMaterial);
        static Mesh*      parseMesh(aiMesh* aMesh, const aiScene* aScene, math::vec3& out_Min, math::vec3& out_Max);
        static Material*  parseMaterial(Renderer* renderer, aiMaterial* aMaterial, const aiScene* aScene, std::string directory);

        static std::string processPath(aiString* path, std::string directory);
    };
}

#endif //RESOURCES_MESH_LOADER_HPP