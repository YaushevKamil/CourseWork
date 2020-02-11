#ifndef MESH_LINE_STRIP_HPP
#define MESH_LINE_STRIP_HPP

#include "mesh.hpp"

namespace Engine {
    class LineStrip : public Mesh {
    public:
        LineStrip(float width, unsigned int segments);
    };
}

#endif //MESH_LINE_STRIP_HPP
