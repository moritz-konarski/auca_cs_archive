#ifndef MESH_GENERATORS_HPP
#define MESH_GENERATORS_HPP

#include "aur.hpp"

namespace aur {
    namespace mesh_generators {

        std::shared_ptr<Mesh>
        generate_triangle_mesh(float size, std::string name, glm::vec3 position,
                               std::vector<glm::vec4> color_array,
                               std::shared_ptr<Material> material) {
            int color_array_length = color_array.size();
            auto triangle_vertices = geometry_generators::generate_triangle_geometry_data(size);
            for (int i = 0; i < triangle_vertices.second.size(); ++i) {
                triangle_vertices.second[i].color = color_array.at(i % color_array_length);
            }
            auto triangle_geometry = std::make_shared<ES2Geometry>(triangle_vertices.first,
                                                                   triangle_vertices.second);
            auto triangle = std::make_shared<Mesh>(triangle_geometry, material, position);
            triangle->set_name(name);
            return triangle;
        }

        std::shared_ptr<Mesh>
        generate_triangle_mesh(float size, std::string name, glm::vec3 position,
                               glm::vec4 color, std::shared_ptr<Material> material) {
            auto triangle_vertices = geometry_generators::generate_triangle_geometry_data(size);
            for (int i = 0; i < triangle_vertices.second.size(); ++i) {
                triangle_vertices.second[i].color = color;
            }
            auto triangle_geometry = std::make_shared<ES2Geometry>(triangle_vertices.first,
                                                                   triangle_vertices.second);
            auto triangle = std::make_shared<Mesh>(triangle_geometry, material, position);
            triangle->set_name(name);
            return triangle;
        }

        std::shared_ptr<Mesh>
        generate_rectangle_mesh(float width, float height, std::string name, glm::vec3 position,
                                std::vector<glm::vec4> color_array,
                                unsigned int width_segments_count,
                                unsigned int height_segments_count,
                                Geometry::Type type, std::shared_ptr<Material> material) {
            int color_array_length = color_array.size();
            auto rectangle_vertices = geometry_generators::generate_plane_geometry_data(width,
                                                                                        height,
                                                                                        width_segments_count,
                                                                                        height_segments_count);
            for (int i = 0; i < rectangle_vertices.second.size(); ++i) {
                rectangle_vertices.second[i].color = color_array.at(i % color_array_length);
            }
            auto rectangle_geometry = std::make_shared<ES2Geometry>(rectangle_vertices.first,
                                                                    rectangle_vertices.second);
            rectangle_geometry->set_type(type);
            auto rectangle = std::make_shared<Mesh>(rectangle_geometry, material, position);
            rectangle->set_name(name);
            return rectangle;
        }

        std::shared_ptr<Mesh>
        generate_rectangle_mesh(float width, float height, std::string name, glm::vec3 position,
                                glm::vec4 color,
                                unsigned int width_segments_count,
                                unsigned int height_segments_count,
                                Geometry::Type type, std::shared_ptr<Material> material) {
            auto rectangle_vertices = geometry_generators::generate_plane_geometry_data(width,
                                                                                        height,
                                                                                        width_segments_count,
                                                                                        height_segments_count);
            for (int i = 0; i < rectangle_vertices.second.size(); ++i) {
                rectangle_vertices.second[i].color = color;
            }
            auto rectangle_geometry = std::make_shared<ES2Geometry>(rectangle_vertices.first,
                                                                    rectangle_vertices.second);
            rectangle_geometry->set_type(type);
            auto rectangle = std::make_shared<Mesh>(rectangle_geometry, material, position);
            rectangle->set_name(name);
            return rectangle;
        }


        std::shared_ptr<Mesh>
        generate_circle_mesh(float radius, std::string name, glm::vec3 position,
                             std::vector<glm::vec4> color_array, unsigned int segment_count,
                             Geometry::Type type, std::shared_ptr<Material> material) {
            int color_array_length = color_array.size();
            auto circle_vertices = geometry_generators::generate_circle_geometry_data(radius,
                                                                                      segment_count);
            for (int i = 0; i < circle_vertices.second.size(); ++i) {
                circle_vertices.second[i].color = color_array.at(i % color_array_length);
            }
            auto circle_geometry = std::make_shared<ES2Geometry>(circle_vertices.first,
                                                                 circle_vertices.second);
            circle_geometry->set_type(type);
            auto circle = std::make_shared<Mesh>(circle_geometry, material, position);
            circle->set_name(name);
            return circle;
        }

        std::shared_ptr<Mesh>
        generate_circle_mesh(float radius, std::string name, glm::vec3 position,
                             glm::vec4 color, unsigned int segment_count,
                             Geometry::Type type, std::shared_ptr<Material> material) {
            auto circle_vertices = geometry_generators::generate_circle_geometry_data(radius,
                                                                                      segment_count);
            for (int i = 0; i < circle_vertices.second.size(); ++i) {
                circle_vertices.second[i].color = color;
            }
            auto circle_geometry = std::make_shared<ES2Geometry>(circle_vertices.first,
                                                                 circle_vertices.second);
            circle_geometry->set_type(type);
            auto circle = std::make_shared<Mesh>(circle_geometry, material, position);
            circle->set_name(name);
            return circle;
        }

        std::shared_ptr<Mesh>
        generate_sphere_mesh(float radius, std::string name, glm::vec3 position,
                             std::vector<glm::vec4> color_array, unsigned int segment_count,
                             unsigned int ring_count, Geometry::Type type,
                             std::shared_ptr<Material> material) {
            int color_array_length = color_array.size();
            auto sphere_vertices = geometry_generators::generate_sphere_geometry_data(radius,
                                                                                      segment_count,
                                                                                      ring_count);
            for (int i = 0; i < sphere_vertices.second.size(); ++i) {
                sphere_vertices.second[i].color = color_array.at(i % color_array_length);
            }
            auto sphere_geometry = std::make_shared<ES2Geometry>(sphere_vertices.first,
                                                                 sphere_vertices.second);
            sphere_geometry->set_type(type);
            auto sphere = std::make_shared<Mesh>(sphere_geometry, material, position);
            sphere->set_name(name);
            return sphere;
        }

        std::shared_ptr<Mesh>
        generate_sphere_mesh(float radius, std::string name, glm::vec3 position,
                             glm::vec4 color, unsigned int segment_count,
                             unsigned int ring_count, Geometry::Type type,
                             std::shared_ptr<Material> material) {
            auto sphere_vertices = geometry_generators::generate_sphere_geometry_data(radius,
                                                                                      segment_count,
                                                                                      ring_count);
            for (int i = 0; i < sphere_vertices.second.size(); ++i) {
                sphere_vertices.second[i].color = color;
            }
            auto sphere_geometry = std::make_shared<ES2Geometry>(sphere_vertices.first,
                                                                 sphere_vertices.second);
            sphere_geometry->set_type(type);
            auto sphere = std::make_shared<Mesh>(sphere_geometry, material, position);
            sphere->set_name(name);
            return sphere;
        }
    }
}

#endif
