#ifndef MESH_CIRCLE_HPP
#define MESH_CIRCLE_HPP

#include "mesh.hpp"

namespace Engine {
    class Circle : public Mesh {
    public:
        Circle(unsigned int edgeSegments, unsigned int ringSegments);
    };
}

#endif //MESH_CIRCLE_HPP