#ifndef MESH_PLANE_HPP
#define MESH_PLANE_HPP

#include "mesh.hpp"

namespace Engine {
    class Plane : public Mesh {
    public:
        Plane(unsigned int xSegments, unsigned int ySegments);
    };
}

#endif //MESH_PLANE_HPP
