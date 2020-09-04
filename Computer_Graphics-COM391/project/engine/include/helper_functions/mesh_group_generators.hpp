#ifndef MESH_GROUP_GENERATORS_HPP
#define MESH_GROUP_GENERATORS_HPP

#include "aur.hpp"
#include "mesh_generators.hpp"

namespace helper_functions {
    using namespace aur;

    void generate_circle_ring(std::shared_ptr<Mesh> parent_object,
                              Circle_Data circle_base_data,
                              Mesh_Data circle_base_mesh_data,
                              float circle_radius,
                              unsigned int circle_count,
                              unsigned int modulus_value,
                              float z_offset) {
        float angle = 0;
        float angle_ratio = 2.0f * M_PI / circle_count;
        for (int i = 1; i <= circle_count; ++i) {
            if (i % modulus_value != 0) {
                angle = angle_ratio * i;
                circle_base_mesh_data.position = glm::vec3{
                        circle_radius * cos(angle), circle_radius * sin(angle),
                        z_offset};
                auto circle = generate_circle_mesh(circle_base_data,
                                                   circle_base_mesh_data);
                char name[15];
                sprintf(name, "circle %d", i);
                circle->set_name(name);
                parent_object->add_child(circle);
            }
        }
    }

    void generate_square_ring(std::shared_ptr<Mesh> parent_object,
                              Square_Data square_base_data,
                              Mesh_Data square_base_mesh_data,
                              float circle_radius,
                              unsigned int square_count,
                              unsigned int modulus_value,
                              float z_offset) {
        float angle = 0;
        float angle_ratio = 2.0f * M_PI / square_count;
        for (int i = 1; i <= square_count; ++i) {
            if (i % modulus_value != 0) {
                angle = angle_ratio * i;
                square_base_mesh_data.position = glm::vec3{
                        (circle_radius) * cos(angle), (circle_radius) * sin(angle),
                        z_offset};
                auto square = generate_square_mesh(square_base_data,
                                                   square_base_mesh_data);
                char name[15];
                sprintf(name, "square %d", i);
                square->set_rotation_z(M_PI / 4.0f);
                square->set_name(name);
                parent_object->add_child(square);
            }
        }
    }

    std::shared_ptr<Mesh>
    generate_cube(glm::vec3 position, Square_Data square_data, Mesh_Data mesh_data) {
        //TODO: rotate the sides correctly
        auto center = generate_vector_mesh(glm::vec3{0.0f}, glm::vec3{0.0f},
                                           color::WHITE, mesh_data.material);
        float r = square_data.side_length / 2.0f;
        for (int i = 0; i < 4; ++i) {
            float angle = M_PI / 2.0f * static_cast<float>(i);
            mesh_data.position = glm::vec3{r * cosf(angle), 0.0f, r * sinf(angle)};
            auto square = generate_square_mesh(square_data, mesh_data);
            square->set_rotation_y(-angle + M_PI / 2.0f);
            center->add_child(square);
        }
        for (int i = 0; i < 2; ++i) {
            float angle = M_PI * static_cast<float>(i) + M_PI/2.0f;
            mesh_data.position = glm::vec3(0.0f, r * sinf(angle), r * cosf(angle));
            auto square = generate_square_mesh(square_data, mesh_data);
            square->set_rotation_x(-angle);
            center->add_child(square);
        }
        center->set_position(position);
        return center;
    }
}

#endif
