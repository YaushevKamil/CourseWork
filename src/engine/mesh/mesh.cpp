#include "mesh.hpp"

namespace Engine {
    Mesh::Mesh() {}

    Mesh::Mesh(std::vector<math::vec3> positions, std::vector<unsigned int> indices) {
        Positions = positions;
        Indices = indices;
    }

    Mesh::Mesh(std::vector<math::vec3> positions, std::vector<math::vec2> uv, std::vector<unsigned int> indices) {
        Positions = positions;
        UV = uv;
        Indices = indices;
    }

    Mesh::Mesh(std::vector<math::vec3> positions, std::vector<math::vec2> uv, std::vector<math::vec3> normals, std::vector<unsigned int> indices) {
        Positions = positions;
        UV = uv;
        Normals = normals;
        Indices = indices;
    }

    Mesh::Mesh(std::vector<math::vec3> positions, std::vector<math::vec2> uv, std::vector<math::vec3> normals, std::vector<math::vec3> tangents, std::vector<math::vec3> bitangents, std::vector<unsigned int> indices) {
        Positions = positions;
        UV = uv;
        Normals = normals;
        Tangents = tangents;
        Bitangents = bitangents;
        Indices = indices;
    }

    void Mesh::SetPositions(std::vector<math::vec3> positions) {
        Positions = positions;
    }

    void Mesh::SetUVs(std::vector<math::vec2> uv) {
        UV = uv;
    }

    void Mesh::SetNormals(std::vector<math::vec3> normals) {
        Normals = normals;
    }

    void Mesh::SetTangents(std::vector<math::vec3> tangents, std::vector<math::vec3> bitangents) {
        Tangents = tangents;
        Bitangents = bitangents;
    }

    void Mesh::Finalize(bool interleaved) {
        if (!m_VAO) {
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);
        }

        std::vector<float> data;
        if (interleaved) {
            for (int i = 0; i < Positions.size(); ++i) {
                data.push_back(Positions[i].x);
                data.push_back(Positions[i].y);
                data.push_back(Positions[i].z);
                if (UV.size() > 0) {
                    data.push_back(UV[i].x);
                    data.push_back(UV[i].y);
                }
                if (Normals.size() > 0) {
                    data.push_back(Normals[i].x);
                    data.push_back(Normals[i].y);
                    data.push_back(Normals[i].z);
                }
                if (Tangents.size() > 0) {
                    data.push_back(Tangents[i].x);
                    data.push_back(Tangents[i].y);
                    data.push_back(Tangents[i].z);
                }
                if (Bitangents.size() > 0) {
                    data.push_back(Bitangents[i].x);
                    data.push_back(Bitangents[i].y);
                    data.push_back(Bitangents[i].z);
                }
            }
        } else {
            for (int i = 0; i < Positions.size(); ++i) {
                data.push_back(Positions[i].x);
                data.push_back(Positions[i].y);
                data.push_back(Positions[i].z);
            }
            for (int i = 0; i < UV.size(); ++i) {
                data.push_back(UV[i].x);
                data.push_back(UV[i].y);
            }
            for (int i = 0; i < Normals.size(); ++i) {
                data.push_back(Normals[i].x);
                data.push_back(Normals[i].y);
                data.push_back(Normals[i].z);
            }
            for (int i = 0; i < Tangents.size(); ++i) {
                data.push_back(Tangents[i].x);
                data.push_back(Tangents[i].y);
                data.push_back(Tangents[i].z);
            }
            for (int i = 0; i < Bitangents.size(); ++i) {
                data.push_back(Bitangents[i].x);
                data.push_back(Bitangents[i].y);
                data.push_back(Bitangents[i].z);
            }
        }

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        if (Indices.size() > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
        }
        if (interleaved) {
            size_t stride                      = 3 * sizeof(float);
            if (UV.size() > 0)         stride += 2 * sizeof(float);
            if (Normals.size() > 0)    stride += 3 * sizeof(float);
            if (Tangents.size() > 0)   stride += 3 * sizeof(float);
            if (Bitangents.size() > 0) stride += 3 * sizeof(float);

            size_t offset = 0;
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 3 * sizeof(float);
            if (UV.size() > 0) {
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
                offset += 2 * sizeof(float);
            }
            if (Normals.size() > 0) {
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
                offset += 3 * sizeof(float);
            }
            if (Tangents.size() > 0) {
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
                offset += 3 * sizeof(float);
            }
            if (Bitangents.size() > 0) {
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
                offset += 3 * sizeof(float);
            }
        } else {
            size_t offset = 0;
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += Positions.size() * sizeof(float);
            if (UV.size() > 0) {
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
                offset += UV.size() * sizeof(float);
            }
            if (Normals.size() > 0) {
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
                offset += Normals.size() * sizeof(float);
            }
            if (Tangents.size() > 0) {
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
                offset += Tangents.size() * sizeof(float);
            }
            if (Bitangents.size() > 0) {
                glEnableVertexAttribArray(4);
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
                offset += Bitangents.size() * sizeof(float);
            }
        }
        glBindVertexArray(0);
    }

    void Mesh::Clear() {
        Positions.clear();
        UV.clear();
        Normals.clear();
        Tangents.clear();
        Bitangents.clear();
        Indices.clear();
    }
}