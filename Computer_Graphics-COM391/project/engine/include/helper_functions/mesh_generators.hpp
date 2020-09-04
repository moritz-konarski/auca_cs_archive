#ifndef MESH_GENERATORS_HPP
#define MESH_GENERATORS_HPP

#include "aur.hpp"
#include "helpers.hpp"

namespace helper_functions {
    using namespace aur;

    std::shared_ptr<Mesh>
    generate_triangle_mesh(helper_functions::Triangle_Data triangle_data,
                           helper_functions::Mesh_Data mesh_data) {
        int color_array_length = mesh_data.color_array.size();
        auto triangle_vertices = geometry_generators::generate_triangle_geometry_data(
                triangle_data.size);
        for (int i = 0; i < triangle_vertices.second.size(); ++i) {
            triangle_vertices.second[i].color = mesh_data.color_array.at(
                    i % color_array_length);
        }
        auto triangle_geometry = std::make_shared<ES2Geometry>(
                triangle_vertices.first,
                triangle_vertices.second);
        auto triangle = std::make_shared<Mesh>(triangle_geometry, mesh_data.material,
                                               mesh_data.position);
        triangle->set_name(mesh_data.name);
        return triangle;
    }

    std::shared_ptr<Mesh>
    generate_vector_mesh(glm::vec3 position, glm::vec3 vector, glm::vec4 color,
                         std::shared_ptr<Material> material) {
        auto vector_data = geometry_generators::generate_vector_geometry_data(
                position, vector);
        vector_data.second.at(0).color = color;
        vector_data.second.at(1).color = color;
        auto vector_geometry = std::make_shared<ES2Geometry>(vector_data.first,
                                                             vector_data.second);
        vector_geometry->set_line_width(15.0f);
        vector_geometry->set_type(Geometry::Type::Lines);
        material->set_line_width(15.0f);
        material->set_face_culling_enabled(false);
        auto vec = std::make_shared<Mesh>(vector_geometry, material,
                                             position);
        material->set_line_width(1.0f);
        material->set_face_culling_enabled(true);
        return vec;
    }

    std::shared_ptr<Mesh>
    generate_rectangle_mesh(helper_functions::Rectangle_Data rectangle_data,
                            helper_functions::Mesh_Data mesh_data) {
        int color_array_length = mesh_data.color_array.size();
        auto rectangle_vertices = geometry_generators::generate_plane_geometry_data(
                rectangle_data.width,
                rectangle_data.height,
                rectangle_data.width_segments_count,
                rectangle_data.height_segments_count);
        for (int i = 0; i < rectangle_vertices.second.size(); ++i) {
            rectangle_vertices.second[i].color = mesh_data.color_array.at(
                    i % color_array_length);
        }
        auto rectangle_geometry = std::make_shared<ES2Geometry>(
                rectangle_vertices.first,
                rectangle_vertices.second);
        rectangle_geometry->set_type(mesh_data.geometry_type);
        auto rectangle = std::make_shared<Mesh>(rectangle_geometry,
                                                mesh_data.material,
                                                mesh_data.position);
        rectangle->set_name(mesh_data.name);
        return rectangle;
    }

    std::shared_ptr<Mesh>
    generate_square_mesh(helper_functions::Square_Data square_data,
                         helper_functions::Mesh_Data mesh_data) {
        int color_array_length = mesh_data.color_array.size();
        auto square_vertices = geometry_generators::generate_plane_geometry_data(
                square_data.side_length,
                square_data.side_length,
                square_data.segment_count,
                square_data.segment_count);
        for (int i = 0; i < square_vertices.second.size(); ++i) {
            square_vertices.second[i].color = mesh_data.color_array.at(
                    i % color_array_length);
        }
        auto square_geometry = std::make_shared<ES2Geometry>(
                square_vertices.first,
                square_vertices.second);
        square_geometry->set_type(mesh_data.geometry_type);
        auto square = std::make_shared<Mesh>(square_geometry, mesh_data.material,
                                             mesh_data.position);
        square->set_name(mesh_data.name);
        return square;
    }

    std::shared_ptr<Mesh>
    generate_circle_mesh(helper_functions::Circle_Data circle_data,
                         helper_functions::Mesh_Data mesh_data) {
        int color_array_length = mesh_data.color_array.size();
        auto circle_vertices = geometry_generators::generate_circle_geometry_data(
                circle_data.radius,
                circle_data.segment_count);
        for (int i = 0; i < circle_vertices.second.size(); ++i) {
            circle_vertices.second[i].color = mesh_data.color_array.at(
                    i % color_array_length);
        }
        auto circle_geometry = std::make_shared<ES2Geometry>(
                circle_vertices.first,
                circle_vertices.second);
        circle_geometry->set_type(mesh_data.geometry_type);
        auto circle = std::make_shared<Mesh>(circle_geometry, mesh_data.material,
                                             mesh_data.position);
        circle->set_name(mesh_data.name);
        return circle;
    }

    std::shared_ptr<Mesh>
    generate_sphere_mesh(helper_functions::Sphere_Data sphere_data,
                         helper_functions::Mesh_Data mesh_data) {
        int color_array_length = mesh_data.color_array.size();
        auto sphere_vertices = geometry_generators::generate_sphere_geometry_data(
                sphere_data.radius,
                sphere_data.segment_count,
                sphere_data.ring_count);
        for (int i = 0; i < sphere_vertices.second.size(); ++i) {
            sphere_vertices.second[i].color = mesh_data.color_array.at(
                    i % color_array_length);
        }
        auto sphere_geometry = std::make_shared<ES2Geometry>(
                sphere_vertices.first,
                sphere_vertices.second);
        sphere_geometry->set_type(mesh_data.geometry_type);
        auto sphere = std::make_shared<Mesh>(sphere_geometry, mesh_data.material,
                                             mesh_data.position);
        sphere->set_name(mesh_data.name);
        return sphere;
    }
}

#endif
