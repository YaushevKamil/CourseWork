#ifndef MESH_MESH_HPP
#define MESH_MESH_HPP

#include <vector>
#include <functional>

#include "../glad/glad.h"
#include "../math/math.hpp"
#include "../utility/logging/log.hpp"

namespace Engine {
    enum TOPOLOGY {
        POINTS,
        LINES,
        LINE_STRIP,
        TRIANGLES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
    };

    class Mesh {
        // TODO: make private and only visible to renderer (as a friend class)
    public:
        unsigned int m_VAO = 0;
        unsigned int m_VBO;
        unsigned int m_EBO;
    public:
        std::vector<math::vec3> Positions;
        std::vector<math::vec2> UV;
        std::vector<math::vec3> Normals;
        std::vector<math::vec3> Tangents;
        std::vector<math::vec3> Bitangents;

        TOPOLOGY Topology = TRIANGLES;
        std::vector<unsigned int> Indices;

        Mesh();
        Mesh(std::vector<math::vec3> positions, std::vector<unsigned int> indices);
        Mesh(std::vector<math::vec3> positions, std::vector<math::vec2> uv, std::vector<unsigned int> indices);
        Mesh(std::vector<math::vec3> positions, std::vector<math::vec2> uv, std::vector<math::vec3> normals, std::vector<unsigned int> indices);
        Mesh(std::vector<math::vec3> positions, std::vector<math::vec2> uv, std::vector<math::vec3> normals, std::vector<math::vec3> tangents, std::vector<math::vec3> bitangents, std::vector<unsigned int> indices);

        // set vertex data manually
        void SetPositions(std::vector<math::vec3> positions);
        void SetUVs(std::vector<math::vec2> uv);
        void SetNormals(std::vector<math::vec3> normals);
        void SetTangents(std::vector<math::vec3> tangents, std::vector<math::vec3> bitangents);

        void Finalize(bool interleaved = true);
        void Clear();
    };
}

#endif //MESH_MESH_HPP