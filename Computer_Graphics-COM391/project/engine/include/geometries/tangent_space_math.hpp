#ifndef TANGENT_SPACE_MATH_HPP
#define TANGENT_SPACE_MATH_HPP

#include <queue>
#include <aur.hpp>
#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include "geometry_generators.hpp"

namespace aur {
    void calculate_tangent_space(std::vector<unsigned int> indices,
                                 std::vector<Vertex> vertices) {
        unsigned int length = indices.size();
        for (unsigned int i = 0; i < length - 3; i += 3) {
            Vertex *v1 = &vertices.at(indices.at(i));
            Vertex *v2 = &vertices.at(indices.at(i+1));
            Vertex *v3 = &vertices.at(indices.at(i+2));

            glm::vec3 normal = v1->normal;
            std::cout << "normal\t\t" << glm::to_string(normal) << std::endl;

            glm::vec3 edge1 = v2->position - v1->position;
            std::cout << "edge1\t\t" << glm::to_string(edge1) << std::endl;

            glm::vec3 edge2 = v3->position - v1->position;
            std::cout << "edge2\t\t" << glm::to_string(edge2) << std::endl;

            glm::vec4 deltaUV1 = v2->texture1_coordinates - v1->texture1_coordinates;
            std::cout << "deltaUV1\t" << glm::to_string(deltaUV1) << std::endl;

            glm::vec4 deltaUV2 = v3->texture1_coordinates - v1->texture1_coordinates;
            std::cout << "deltaUV2\t" << glm::to_string(deltaUV2) << std::endl;

            float f = 1;
            glm::vec3 tangent, bitangent;

            if (deltaUV1.x * deltaUV2.y != deltaUV2.x * deltaUV1.y) {
                f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
                tangent = {edge1 * deltaUV2.y - edge2 * deltaUV1.y};
                tangent *= f;
                tangent = glm::normalize(tangent);
                std::cout << "tangent\t\t" << glm::to_string(tangent)
                        << std::endl;

                bitangent = {edge2 * deltaUV1.x - edge1 * deltaUV2.x};
                bitangent *= f;
                bitangent = glm::normalize(bitangent);
                std::cout << "bitangent\t" << glm::to_string(bitangent)
                        << std::endl;
            } else {
                tangent = {1.0f, 0.0f, 0.0f};
                std::cout << "tangent\t\t" << glm::to_string(tangent)
                          << std::endl;

                bitangent = {0.0f, 1.0f, 0.0f};
                std::cout << "bitangent\t" << glm::to_string(bitangent)
                          << std::endl;
            }
            //tangent = glm::normalize(tangent - normal * glm::dot(normal, tangent));

            v1->tangent = tangent;
            v1->bitangent = bitangent;
            v2->tangent = tangent;
            v2->bitangent = bitangent;
            v3->tangent = tangent;
            v3->bitangent = bitangent;
        }
    }
}

#endif
