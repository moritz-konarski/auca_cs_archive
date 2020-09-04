#ifndef TEXTURE_GENERATORS
#define TEXTURE_GENERATORS

#include "aur.hpp"

namespace texture_generators {
    using namespace aur;

    std::shared_ptr<ES2Texture> generate_texture(const std::string image_path) {

        auto[image_data, image_width, image_height, image_channels] = file_utilities::read_image_file(
                image_path);
        return std::make_shared<ES2Texture>(image_data, image_width, image_height,
                                            image_channels);
    }

    void set_texture_attributes(std::shared_ptr<ES2Texture> texture) {};

}
#endif