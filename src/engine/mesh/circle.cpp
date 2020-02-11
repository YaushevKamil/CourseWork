#include "circle.hpp"

namespace Engine {
    Circle::Circle(unsigned int edgeSegments, unsigned int ringSegments) {
        for (unsigned int y = 0; y <= ringSegments; ++y) {
            for (unsigned int x = 0; x <= edgeSegments; ++x) {
                float xSegment = (float)x / (float)edgeSegments;
                float ringDepth = (float)y / (float)ringSegments;
                float xPos = std::cos(xSegment * math::TAU);
                float yPos = std::sin(xSegment * math::TAU);

                Positions.push_back(math::vec3(xPos * ringDepth, yPos * ringDepth, 0.0f));
            }
        }
        bool oddRow = false;
        for (int y = 0; y < ringSegments; ++y) {
            if (!oddRow) {
                for (int x = 0; x <= edgeSegments; ++x) {
                    Indices.push_back(y       * (edgeSegments + 1) + x);
                    Indices.push_back((y + 1) * (edgeSegments + 1) + x);
                }
            } else {
                for (int x = edgeSegments; x >= 0; --x) {
                    Indices.push_back((y + 1) * (edgeSegments + 1) + x);
                    Indices.push_back(y       * (edgeSegments + 1) + x);
                }
            }
            oddRow = !oddRow;
        }

        Topology = TRIANGLE_STRIP;
        Finalize();
    }
}