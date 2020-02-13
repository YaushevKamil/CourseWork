#include "sphere.hpp"

namespace Engine {
    Sphere::Sphere(unsigned int xSegments, unsigned int ySegments) {
        for (unsigned int y = 0; y <= ySegments; ++y) {
            for (unsigned int x = 0; x <= xSegments; ++x) {
                float xSegment = (float)x / (float)xSegments;
                float ySegment = (float)y / (float)ySegments;
                float xPos = std::cos(xSegment * math::TAU) * std::sin(ySegment * math::PI);
                float yPos = std::cos(ySegment * math::PI);
                float zPos = std::sin(xSegment * math::TAU) * std::sin(ySegment * math::PI);

                Positions.push_back(math::vec3(xPos, yPos, zPos));
                UV.push_back(math::vec2(xSegment, ySegment));
                Normals.push_back(math::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (int y = 0; y < ySegments; ++y) {
            for (int x = 0; x < xSegments; ++x) {
                Indices.push_back((y + 1) * (xSegments + 1) + x);
                Indices.push_back(y       * (xSegments + 1) + x);
                Indices.push_back(y       * (xSegments + 1) + x + 1);

                Indices.push_back((y + 1) * (xSegments + 1) + x);
                Indices.push_back(y       * (xSegments + 1) + x + 1);
                Indices.push_back((y + 1) * (xSegments + 1) + x + 1);
            }
        }

        Topology = TRIANGLES;
        Finalize();
    }
}