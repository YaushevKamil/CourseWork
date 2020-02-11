#ifndef MESH_QUAD_HPP
#define MESH_QUAD_HPP

#include "mesh.hpp"

namespace Engine {
    class Quad : public Mesh {
    public:
        Quad();
        Quad(float width, float height);
    };
}

#endif //MESH_QUAD_HPP