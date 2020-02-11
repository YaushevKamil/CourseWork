#ifndef MESH_SPHERE_HPP
#define MESH_SPHERE_HPP

#include "mesh.hpp"

namespace Engine {
    class Sphere : public Mesh {
    public:
        Sphere(unsigned int xSegments, unsigned int ySegments);
    };
}

#endif //MESH_SPHERE_HPP
