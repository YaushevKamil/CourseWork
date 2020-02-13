#ifndef MESH_TORUS_HPP
#define MESH_TORUS_HPP

#include "mesh.hpp"

namespace Engine {
    class Torus : public Mesh {
    public:
        Torus(float r1, float r2, unsigned int lod1, unsigned int lod2);
    };
}

#endif //MESH_TORUS_HPP