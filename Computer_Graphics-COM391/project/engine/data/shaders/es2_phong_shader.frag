// define light counts
#ifndef DIRECTIONAL_LIGHT_COUNT
#define DIRECTIONAL_LIGHT_COUNT 1
#endif
#ifndef POINT_LIGHT_COUNT
#define POINT_LIGHT_COUNT 1
#endif
#ifndef SPOT_LIGHT_COUNT
#define SPOT_LIGHT_COUNT 1
#endif

// define texturing modes
#ifndef TEXTURING_MODE_ADDITION
#define TEXTURING_MODE_ADDITION 0
#endif
#ifndef TEXTURING_MODE_SUBTRACTION
#define TEXTURING_MODE_SUBTRACTION 1
#endif
#ifndef TEXTURING_MODE_REVERSE_SUBTRACTION
#define TEXTURING_MODE_REVERSE_SUBTRACTION 2
#endif
#ifndef TEXTURING_MODE_MODULATION
#define TEXTURING_MODE_MODULATION 3
#endif
#ifndef TEXTURING_MODE_DECALING
#define TEXTURING_MODE_DECALING 4
#endif

// define fog types
#ifndef FOG_TYPE_LINEAR
#define FOG_TYPE_LINEAR 0
#endif
#ifndef FOG_TYPE_EXP
#define FOG_TYPE_EXP 1
#endif
#ifndef FOG_TYPE_EXP2
#define FOG_TYPE_EXP2 2
#endif

// define for characteristics
#ifndef FOG_DEPTH_PLANAR
#define FOG_DEPTH_PLANAR 0
#endif
#ifndef FOG_DEPTH_PLANAR_ABSOLUTE
#define FOG_DEPTH_PLANAR_ABSOLUTE 1
#endif
#ifndef FOG_DEPTH_RADIAL
#define FOG_DEPTH_RADIAL 2
#endif

uniform vec3 ambient_light_color;           // color of the light that is always there
uniform vec3 material_ambient_color;        // color of material in ambient light

// lighting mode that takes the angle of light to fragment into account
// uses normal vector. Dot product of the two vectors gives impact the light has on the surface
uniform vec4 material_diffuse_color;        // color of material in diffuse light
uniform vec4 material_emission_color;       // color of light emitted by the material
uniform vec3 material_specular_color;       // color of light from specular reflection
uniform float material_specular_exponent;   // impacts the scattering and radius of the highlight

uniform bool texture2_is_normal_map;        // is the second texture a normal map?

#if DIRECTIONAL_LIGHT_COUNT > 0
uniform bool directional_light_enabled[DIRECTIONAL_LIGHT_COUNT];
uniform bool directional_light_two_sided[DIRECTIONAL_LIGHT_COUNT];
uniform vec3 directional_light_view_direction[DIRECTIONAL_LIGHT_COUNT];
uniform vec3 directional_light_ambient_color[DIRECTIONAL_LIGHT_COUNT];
uniform vec3 directional_light_diffuse_color[DIRECTIONAL_LIGHT_COUNT];
uniform vec3 directional_light_specular_color[DIRECTIONAL_LIGHT_COUNT];
uniform float directional_light_intensity[DIRECTIONAL_LIGHT_COUNT];
#endif

#if POINT_LIGHT_COUNT > 0
uniform bool point_light_enabled[POINT_LIGHT_COUNT];
uniform bool point_light_two_sided[POINT_LIGHT_COUNT];
uniform vec3 point_light_view_position[POINT_LIGHT_COUNT];
uniform vec3 point_light_ambient_color[POINT_LIGHT_COUNT];
uniform vec3 point_light_diffuse_color[POINT_LIGHT_COUNT];
uniform vec3 point_light_specular_color[POINT_LIGHT_COUNT];
uniform float point_light_intensity[POINT_LIGHT_COUNT];
uniform float point_light_constant_attenuation[POINT_LIGHT_COUNT];
uniform float point_light_linear_attenuation[POINT_LIGHT_COUNT];
uniform float point_light_quadratic_attenuation[POINT_LIGHT_COUNT];
#endif

#if SPOT_LIGHT_COUNT > 0
uniform bool spot_light_enabled[SPOT_LIGHT_COUNT];
uniform bool spot_light_two_sided[SPOT_LIGHT_COUNT];
uniform vec3 spot_light_view_position[SPOT_LIGHT_COUNT];
uniform vec3 spot_light_view_direction[SPOT_LIGHT_COUNT];
uniform vec3 spot_light_ambient_color[SPOT_LIGHT_COUNT];
uniform vec3 spot_light_diffuse_color[SPOT_LIGHT_COUNT];
uniform vec3 spot_light_specular_color[SPOT_LIGHT_COUNT];
uniform float spot_light_exponent[SPOT_LIGHT_COUNT];
uniform float spot_light_cutoff_angle_cosine[SPOT_LIGHT_COUNT];
uniform float spot_light_intensity[SPOT_LIGHT_COUNT];
uniform float spot_light_constant_attenuation[SPOT_LIGHT_COUNT];
uniform float spot_light_linear_attenuation[SPOT_LIGHT_COUNT];
uniform float spot_light_quadratic_attenuation[SPOT_LIGHT_COUNT];
#endif

uniform sampler2D texture1_sampler;
uniform bool texture1_enabled;
uniform int texturing_mode1;

uniform sampler2D texture2_sampler;
uniform bool texture2_enabled;
uniform int texturing_mode2;

uniform bool fog_enabled;
uniform int fog_type;
uniform int fog_depth;
uniform vec3 fog_color;
uniform float fog_far_minus_near_plane;
uniform float fog_far_plane;
uniform float fog_density;

varying vec4 fragment_view_position;
varying vec3 fragment_view_direction;
varying vec3 fragment_view_normal;
varying vec4 fragment_color;
varying vec2 fragment_texture1_coordinates;
varying vec2 fragment_texture2_coordinates;
varying mat3 fragment_TBN;

void main() {

    vec3 view_direction;
    vec3 view_normal;

    if (texture2_is_normal_map) {
        view_normal = normalize(texture2D(texture2_sampler,
                                          fragment_texture2_coordinates).rgb * 2.0 - 1.0);
        view_direction = fragment_TBN * normalize(fragment_view_direction);
    } else {
        view_normal = normalize(fragment_view_normal);
        view_direction = normalize(fragment_view_direction);
    }

    vec4 front_color = material_emission_color;
    front_color.rgb += material_ambient_color * ambient_light_color;
    front_color.a   += material_diffuse_color.a;
    vec4 back_color  = front_color;

#if DIRECTIONAL_LIGHT_COUNT > 0
    for (int i = 0; i < DIRECTIONAL_LIGHT_COUNT; i++) {
        if (directional_light_enabled[i]) {

            vec3 dir_light_view;

            if (texture2_is_normal_map) {
                dir_light_view =
                        fragment_TBN * normalize(directional_light_view_direction[i]);
            }

            float n_dot_l = max(
                    dot(view_normal, dir_light_view), 0.0);
            vec3 diffuse_color =
                    material_diffuse_color.rgb * directional_light_diffuse_color[i];
            vec3 diffuse_term = n_dot_l * diffuse_color;

            vec3 reflection_vector = reflect(-dir_light_view,
                                             view_normal);
            float n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
            vec3 specular_color = material_specular_color.rgb *
                                  directional_light_specular_color[i];
            vec3 specular_term =
                    pow(n_dot_h, material_specular_exponent) * specular_color;

            front_color.rgb += directional_light_intensity[i] *
                               (directional_light_ambient_color[i] + diffuse_term +
                                specular_term);

            if (directional_light_two_sided[i]) {
                vec3 inverted_view_normal = -view_normal;

                n_dot_l = max(dot(inverted_view_normal,
                                  dir_light_view), 0.0);
                diffuse_term = n_dot_l * diffuse_color;

                reflection_vector = reflect(-dir_light_view,
                                            inverted_view_normal);
                n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
                specular_term =
                        pow(n_dot_h, material_specular_exponent) * specular_color;

                back_color.rgb += directional_light_intensity[i] *
                                  (directional_light_ambient_color[i] +
                                   diffuse_term + specular_term);
            }
        }
    }
#endif

#if POINT_LIGHT_COUNT > 0
    for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
        if (point_light_enabled[i]) {
            // light direction = light position - fragment position
            vec3 point_light_vector =
                    point_light_view_position[i] + fragment_view_direction;

            // normalize light vector
            float point_light_vector_length = length(point_light_vector);
            point_light_vector /= point_light_vector_length;
            float point_light_vector_length_squared =
                    point_light_vector_length * point_light_vector_length;

            if (texture2_is_normal_map) {
                point_light_vector = fragment_TBN * normalize(point_light_vector);
            }

            // find attenuation factor -- how quickly light drops off relative to
            // distance from object
            float attenuation_factor =
                    (1.0 / (point_light_constant_attenuation[i] +
                            point_light_linear_attenuation[i] *
                            point_light_vector_length +
                            point_light_quadratic_attenuation[i] *
                            point_light_vector_length_squared));
            // apply this factor to light intensity
            attenuation_factor *= point_light_intensity[i];

            // get the dot product of the normal vector and the light vector, non-negative
            float n_dot_l = max(dot(view_normal, point_light_vector), 0.0);
            // get diffuse color as mix of light and material color
            vec3 diffuse_color =
                    material_diffuse_color.rgb * point_light_diffuse_color[i];
            // scale diffuse color by share according to light angle
            vec3 diffuse_term = n_dot_l * diffuse_color;

            // the the vector that reflects off of the material
            vec3 reflection_vector = reflect(-point_light_vector, view_normal);

            // get the dot product of normal vector and reflected light vector
            float n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
            // get specular color as mix of material and light color
            vec3 specular_color =
                    material_specular_color.rgb * point_light_specular_color[i];
            // get the specular color considering the angle of the light
            vec3 specular_term =
                    pow(n_dot_h, material_specular_exponent) * specular_color;
            // add ambient color, diffuse color, and specular color to final color
            front_color.rgb += attenuation_factor *
                               (point_light_ambient_color[i] + diffuse_term +
                                specular_term);

            // if the surface should be lit from both sides
            if (point_light_two_sided[i]) {
                // turn around normal vector
                vec3 inverted_view_normal = -view_normal;

                n_dot_l = max(dot(-inverted_view_normal, point_light_vector), 0.0);
                diffuse_term = n_dot_l * diffuse_color;

                reflection_vector = reflect(-point_light_vector,
                                            inverted_view_normal);

                n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
                specular_term =
                        pow(n_dot_h, material_specular_exponent) * specular_color;

                back_color.rgb += attenuation_factor *
                                  (point_light_ambient_color[i] + diffuse_term +
                                   specular_term);
            }
        }
    }
#endif

#if SPOT_LIGHT_COUNT > 0
    for (int i = 0; i < SPOT_LIGHT_COUNT; ++i) {
        if (spot_light_enabled[i]) {
            vec3 spot_light_vector =
                    spot_light_view_position[i] - fragment_view_direction;

            float spot_light_vector_length = length(spot_light_vector);
            spot_light_vector /= spot_light_vector_length;

            if (texture2_is_normal_map) {
                spot_light_vector = fragment_TBN * normalize(spot_light_vector);
            }

            float spot_light_vector_lengthSquared =
                    spot_light_vector_length * spot_light_vector_length;
            float attenuation_factor =
                    (1.0 / (spot_light_constant_attenuation[i] +
                            spot_light_linear_attenuation[i] *
                            spot_light_vector_length +
                            spot_light_quadratic_attenuation[i] *
                            spot_light_vector_lengthSquared));
            attenuation_factor *= spot_light_intensity[i];

            float n_dot_l = max(dot(view_normal, spot_light_vector), 0.0);
            vec3 diffuse_color =
                    material_diffuse_color.rgb * spot_light_diffuse_color[i];
            vec3 diffus_term = n_dot_l * diffuse_color;

            vec3 reflection_vector = reflect(-spot_light_vector, view_normal);
            float n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
            vec3 specular_color =
                    material_specular_color.rgb * spot_light_specular_color[i];
            vec3 specular_term =
                    pow(n_dot_h, material_specular_exponent) * specular_color;

            float spot_factor = 0.0;
            float vertex_direction_dot_spot_direction = max(
                    dot(-spot_light_vector, spot_light_view_direction[i]), 0.0);
            if (spot_light_cutoff_angle_cosine[i] <=
                vertex_direction_dot_spot_direction) {
                spot_factor = pow(vertex_direction_dot_spot_direction,
                                  spot_light_exponent[i]);
            }
            attenuation_factor *= spot_factor;

            front_color.rgb += attenuation_factor *
                               (spot_light_ambient_color[i] + diffus_term +
                                specular_term);

            if (spot_light_two_sided[i]) {
                vec3 inverted_view_normal = -view_normal;

                n_dot_l = max(dot(-view_normal, spot_light_vector), 0.0);
                diffus_term = n_dot_l * diffuse_color;

                reflection_vector = reflect(-spot_light_vector,
                                            inverted_view_normal);
                n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
                specular_term =
                        pow(n_dot_h, material_specular_exponent) * specular_color;

                back_color.rgb += attenuation_factor *
                                  (spot_light_ambient_color[i] + diffus_term +
                                   specular_term);
            }
        }
    }
#endif

    gl_FragColor = fragment_color;
    if (gl_FrontFacing) {
        gl_FragColor *= front_color;
    } else {
        gl_FragColor *= back_color;
    }

    if (texture1_enabled) {
        if (texturing_mode1 == TEXTURING_MODE_ADDITION) {
            gl_FragColor += texture2D(texture1_sampler,
                                      fragment_texture1_coordinates);
        } else if (texturing_mode1 == TEXTURING_MODE_MODULATION) {
            gl_FragColor *= texture2D(texture1_sampler,
                                      fragment_texture1_coordinates);
        } else if (texturing_mode1 == TEXTURING_MODE_DECALING) {
            vec4 texel_color = texture2D(texture1_sampler,
                                         fragment_texture1_coordinates);
            gl_FragColor.rgb = mix(gl_FragColor.rgb, texel_color.rgb, texel_color.a);
        } else if (texturing_mode1 == TEXTURING_MODE_SUBTRACTION) {
            gl_FragColor -= texture2D(texture1_sampler,
                                      fragment_texture1_coordinates);
        } else if (texturing_mode1 == TEXTURING_MODE_REVERSE_SUBTRACTION) {
            gl_FragColor =
                    texture2D(texture1_sampler, fragment_texture1_coordinates) -
                    gl_FragColor;
        }
    }

    if (texture2_enabled && !texture2_is_normal_map) {
        if (texturing_mode2 == TEXTURING_MODE_ADDITION) {
            gl_FragColor += texture2D(texture2_sampler,
                                      fragment_texture2_coordinates);
        } else if (texturing_mode2 == TEXTURING_MODE_MODULATION) {
            gl_FragColor *= texture2D(texture2_sampler,
                                      fragment_texture2_coordinates);
        } else if (texturing_mode2 == TEXTURING_MODE_DECALING) {
            vec4 texel_color = texture2D(texture2_sampler,
                                         fragment_texture2_coordinates);
            gl_FragColor.rgb = mix(gl_FragColor.rgb, texel_color.rgb,
                                   texel_color.a);
        } else if (texturing_mode2 == TEXTURING_MODE_SUBTRACTION) {
            gl_FragColor -= texture2D(texture2_sampler,
                                      fragment_texture2_coordinates);
        } else if (texturing_mode2 == TEXTURING_MODE_REVERSE_SUBTRACTION) {
            gl_FragColor =
                    texture2D(texture2_sampler, fragment_texture2_coordinates) -
                    gl_FragColor;
        }
    }

    if (fog_enabled) {
        float fragment_depth;
        if (fog_depth == FOG_DEPTH_PLANAR) {
            fragment_depth = -(fragment_view_position.z / fragment_view_position.w);
        } else if (fog_depth == FOG_DEPTH_PLANAR_ABSOLUTE) {
            fragment_depth = abs(
                    fragment_view_position.z / fragment_view_position.w);
        } else if (fog_depth == FOG_DEPTH_RADIAL) {
            fragment_depth = length(
                    fragment_view_position.xyz / fragment_view_position.w);
        }

        float fragment_fog_factor;
        if (fog_type == FOG_TYPE_LINEAR) {
            fragment_fog_factor =
                    (fog_far_plane - fragment_depth) / fog_far_minus_near_plane;
        } else if (fog_type == FOG_TYPE_EXP) {
            fragment_fog_factor = exp(-1.0 * (fragment_depth * fog_density));
        } else if (fog_type == FOG_TYPE_EXP2) {
            fragment_fog_factor = fragment_depth * fog_density;
            fragment_fog_factor = exp(-(fragment_fog_factor * fragment_fog_factor));
        }
        fragment_fog_factor = clamp(fragment_fog_factor, 0.0, 1.0);

        gl_FragColor.rgb = mix(fog_color, gl_FragColor.rgb, fragment_fog_factor);
    }
}
