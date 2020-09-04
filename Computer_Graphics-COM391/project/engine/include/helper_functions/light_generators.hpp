/*
 * generate point lights based on sphere and its color, given intensity
 */
#ifndef LIGHT_GENERATORS_HPP
#define LIGHT_GENERATORS_HPP

#include "aur.hpp"
#include "mesh_generators.hpp"

namespace helper_functions {
    using namespace aur;

    std::shared_ptr<PointLight>
    generate_point_light(std::shared_ptr<Scene> scene,
                         Sphere_Data lamp_data,
                         Mesh_Data lamp_mesh_data,
                         float intensity) {
        auto point_light = std::make_shared<PointLight>();
        auto lamp_mesh = generate_sphere_mesh(lamp_data, lamp_mesh_data);

        point_light->set_intensity(intensity);
        point_light->add_child(lamp_mesh);
        point_light->set_diffuse_color(
                lamp_mesh->get_geometry()->get_vertices()[0].color);
        scene->get_root()->add_child(point_light);
        scene->get_point_lights().push_back(point_light);
        return point_light;
    }

    std::shared_ptr<PointLight>
    generate_point_light(Sphere_Data lamp_data,
                         Mesh_Data lamp_mesh_data,
                         Point_Light_Data data) {
        auto point_light = std::make_shared<PointLight>();
        auto lamp_mesh = generate_sphere_mesh(lamp_data, lamp_mesh_data);

        point_light->set_intensity(data.intensity);
        point_light->set_position(data.position);
        point_light->set_two_sided(data.is_two_sided);
        point_light->set_diffuse_color(data.color);
        point_light->set_specular_color(data.color);
        point_light->add_child(lamp_mesh);
        point_light->set_diffuse_color(
                lamp_mesh->get_geometry()->get_vertices()[0].color);
        return point_light;
    }

    std::shared_ptr<PointLight> generate_point_light(Point_Light_Data data) {
        auto light = std::make_shared<PointLight>();

        light->set_intensity(data.intensity);
        light->set_position(data.position);
        light->set_two_sided(data.is_two_sided);
        light->set_diffuse_color(data.color);
        light->set_specular_color(data.color);

        return light;
    };
}
#endif