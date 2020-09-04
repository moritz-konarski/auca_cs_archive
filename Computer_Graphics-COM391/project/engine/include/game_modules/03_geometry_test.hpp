#ifndef GEOMETRY_TEST_HPP
#define GEOMETRY_TEST_HPP

#include "constants.hpp"
#include "helpers.hpp"
#include "game_modules.hpp"

namespace game_modules {
    class Geometry_Test : public Game_State {

    public:
        Geometry_Test() {
            using namespace helper_functions;

            _window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                                      constant::WINDOW_FULL_SCREEN);

            auto constant_material = std::make_shared<aur::ES2ConstantMaterial>();
            constant_material->set_face_culling_enabled(false);
            constant_material->set_point_sizing_enabled(true);
            constant_material->set_point_size(3.0f);
            constant_material->set_line_width(1.5f);

            // squares
            Square_Data square_data = {SQUARE_SIDE_LENGTH, SMALL_SEGMENT_COUNT};
            Mesh_Data mesh_data = {constant_material, COLOR_ARRAY, "square 1",
                                   Geometry::Type::Triangles, POSITION_RECTANGLE_1};

            square1 = generate_square_mesh(square_data, mesh_data);

            square_data.segment_count = MEDIUM_SEGMENT_COUNT;
            mesh_data.name = "square 2";
            mesh_data.geometry_type = Geometry::Type::LineLoop;
            mesh_data.position = POSITION_RECTANGLE_2;

            square2 = generate_square_mesh(square_data, mesh_data);

            square_data.segment_count = HIGH_SEGMENT_COUNT;
            mesh_data.name = "square 3";
            mesh_data.geometry_type = Geometry::Type::Points;
            mesh_data.position = POSITION_RECTANGLE_3;

            square3 = generate_square_mesh(square_data, mesh_data);

            // circles
            Circle_Data circle_data = {RADIUS_CIRCLE, SMALL_SEGMENT_COUNT};
            mesh_data.position = POSITION_CIRCLE_1;
            mesh_data.name = "circle 1";
            mesh_data.geometry_type = Geometry::Type::TriangleFan;

            // circles
            circle1 = generate_circle_mesh(circle_data, mesh_data);

            circle_data.segment_count = MEDIUM_SEGMENT_COUNT;
            mesh_data.position = POSITION_CIRCLE_2;
            mesh_data.name = "circle 2";
            mesh_data.geometry_type = Geometry::Type::LineLoop;

            circle2 = generate_circle_mesh(circle_data, mesh_data);

            circle_data.segment_count = HIGH_SEGMENT_COUNT;
            mesh_data.position = POSITION_CIRCLE_3;
            mesh_data.name = "circle 3";
            mesh_data.geometry_type = Geometry::Type::Points;

            circle3 = generate_circle_mesh(circle_data, mesh_data);

            // spheres
            Sphere_Data sphere_data = {RADIUS_SPHERE, SMALL_SEGMENT_COUNT,
                                       RING_COUNT_SPHERE};
            mesh_data.position = POSITION_SPHERE_1;
            mesh_data.name = "sphere 1";
            mesh_data.geometry_type = Geometry::Type::Triangles;

            sphere1 = generate_sphere_mesh(sphere_data, mesh_data);

            sphere_data.segment_count = MEDIUM_SEGMENT_COUNT;
            mesh_data.position = POSITION_SPHERE_2;
            mesh_data.name = "sphere 2";
            mesh_data.geometry_type = Geometry::Type::LineLoop;

            sphere2 = generate_sphere_mesh(sphere_data, mesh_data);

            sphere_data.segment_count = HIGH_SEGMENT_COUNT;
            mesh_data.position = POSITION_SPHERE_3;
            mesh_data.name = "sphere 3";
            mesh_data.geometry_type = Geometry::Type::Points;

            sphere3 = generate_sphere_mesh(sphere_data, mesh_data);

            std::vector<std::shared_ptr<Object>> objects{square1, square2, square3,
                                                         circle1,
                                                         circle2, circle3, sphere1,
                                                         sphere2,
                                                         sphere3};

            _scene = std::make_shared<Scene>(objects);
            _camera = _scene->get_camera();
            _camera->set_z(Z_POSITION_CAMERA);

            helper_functions::set_camera(_camera);
            _window->set_on_key_down(helper_functions::process_keystrokes);
        }

        void draw_loop_actions() override {
            square1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                               ROTATION_SPEED_GEOMETRIES));
            square2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                               ROTATION_SPEED_GEOMETRIES));
            square3->add_to_rotation(
                    glm::vec3(ROTATION_SPEED_GEOMETRIES, -ROTATION_SPEED_GEOMETRIES,
                              0.0f));

            circle1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                               ROTATION_SPEED_GEOMETRIES));
            circle2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                               ROTATION_SPEED_GEOMETRIES));
            circle3->add_to_rotation(
                    glm::vec3(ROTATION_SPEED_GEOMETRIES, -ROTATION_SPEED_GEOMETRIES,
                              0.0f));

            sphere1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                               ROTATION_SPEED_GEOMETRIES));
            sphere2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                               ROTATION_SPEED_GEOMETRIES));
            sphere3->add_to_rotation(
                    glm::vec3(ROTATION_SPEED_GEOMETRIES, -ROTATION_SPEED_GEOMETRIES,
                              0.0f));
        };

    private:
        std::shared_ptr<aur::Mesh> square1, square2, square3, circle1, circle2, circle3, sphere1, sphere2, sphere3;
        std::string TITLE{"geometry test"};

        constexpr static float Z_POSITION_CAMERA{5.0f};

        constexpr static float SQUARE_SIDE_LENGTH{1.0f};
        glm::vec3 POSITION_RECTANGLE_1{-2.0f, 2.0f, 0.0f};
        glm::vec3 POSITION_RECTANGLE_2{0.0f, 2.0f, 0.0f};
        glm::vec3 POSITION_RECTANGLE_3{2.0f, 2.0f, 0.0f};

        float RADIUS_CIRCLE{sqrt(2 * SQUARE_SIDE_LENGTH) / 2.0f};
        glm::vec3 POSITION_CIRCLE_1{-2.0f, 0.0f, 0.0f};
        glm::vec3 POSITION_CIRCLE_2{0.0f, 0.0f, 0.0f};
        glm::vec3 POSITION_CIRCLE_3{2.0f, 0.0f, 0.0f};

        float RADIUS_SPHERE{RADIUS_CIRCLE};
        glm::vec3 POSITION_SPHERE_1{-2.0f, -2.0f, 0.0f};
        glm::vec3 POSITION_SPHERE_2{0.0f, -2.0f, 0.0f};
        glm::vec3 POSITION_SPHERE_3{2.0f, -2.0f, 0.0f};
        constexpr static unsigned int RING_COUNT_SPHERE{16};

        constexpr static float ROTATION_SPEED_GEOMETRIES{0.01f};
        constexpr static int SMALL_SEGMENT_COUNT{8};
        constexpr static int MEDIUM_SEGMENT_COUNT{14};
        constexpr static int HIGH_SEGMENT_COUNT{26};

        std::vector<glm::vec4> COLOR_ARRAY{{color::RED},
                                           {color::GREEN},
                                           {color::BLUE}};
    };
}

#endif
