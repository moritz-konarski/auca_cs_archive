/*
 * generate point lights based on sphere and its color, given intensity
 */
#ifndef LIGHT_GENERATORS_HPP
#define LIGHT_GENERATORS_HPP

#include "aur.hpp"

namespace light_generators {
    using namespace aur;

    std::shared_ptr<PointLight>
    generate_point_light(std::shared_ptr<Scene> scene, std::shared_ptr<Mesh> lamp_mesh_base,
                         float intensity) {
        auto point_light = std::make_shared<PointLight>();
        auto lamp_mesh = std::make_shared<Mesh>(lamp_mesh_base->get_geometry(),
                                                lamp_mesh_base->get_material(),
                                                lamp_mesh_base->get_position());

        point_light->set_intensity(intensity);
        point_light->add_child(lamp_mesh);
        point_light->set_ambient_color(lamp_mesh->get_geometry()->get_vertices()[0].color);
        point_light->set_diffuse_color(lamp_mesh->get_geometry()->get_vertices()[0].color);
        scene->get_root()->add_child(point_light);
        scene->get_point_lights().push_back(point_light);
        return point_light;
    }
}
#endif