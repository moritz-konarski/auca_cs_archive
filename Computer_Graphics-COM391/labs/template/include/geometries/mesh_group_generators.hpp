#ifndef MESH_GROUP_GENERATORS_HPP
#define MESH_GROUP_GENERATORS_HPP

#include "aur.hpp"

namespace aur {
    namespace mesh_group_generators {

        void generate_circle_of_circle_meshes(std::shared_ptr<Mesh> parent_object,
                                              std::shared_ptr<Mesh> circle_base,
                                              float circle_radius, unsigned int circle_count,
                                              unsigned int modulus_value, float z_offset) {
            float angle = 0;
            float angle_ratio = 2.0f * M_PI / circle_count;
            std::shared_ptr<Geometry> circle_base_geometry = circle_base->get_geometry();
            std::shared_ptr<Material> circle_base_material = circle_base->get_material();
            for (int i = 1; i <= circle_count; ++i) {
                if (i % modulus_value != 0) {
                    angle = angle_ratio * i;
                    auto circle = std::make_shared<Mesh>(circle_base_geometry, circle_base_material,
                                                         glm::vec3{circle_radius * cos(angle),
                                                                   circle_radius * sin(angle),
                                                                   z_offset});
                    char name[15];
                    sprintf(name, "circle %d", i);
                    circle->set_name(name);
                    parent_object->add_child(circle);
                }
            }
        }

        void generate_ring_of_square_meshes(std::shared_ptr<Mesh> parent_object,
                                            std::shared_ptr<Mesh> square_base,
                                            float circle_radius, unsigned int square_count,
                                            unsigned int modulus_value, float z_offset) {
            float angle = 0;
            float angle_ratio = 2.0f * M_PI / square_count;
            std::shared_ptr<Geometry> square_base_geometry = square_base->get_geometry();
            std::shared_ptr<Material> square_base_material = square_base->get_material();
            for (int i = 1; i <= square_count; ++i) {
                if (i % modulus_value != 0) {
                    angle = angle_ratio * i;
                    auto square = std::make_shared<Mesh>(square_base_geometry, square_base_material,
                                                         glm::vec3{(circle_radius) * cos(angle),
                                                                   (circle_radius) * sin(angle),
                                                                   z_offset});
                    char name[15];
                    sprintf(name, "square %d", i);
                    square->set_rotation_z(M_PI / 4.0f);
                    square->set_name(name);
                    parent_object->add_child(square);
                }
            }
        }
    }
}

#endif
