#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"
#include "../hpp/Texture.hpp"

Texture::Texture(const std::string& filePath) : filePath(filePath) {

    int w, h, channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(filePath.c_str(), &w, &h, &channels, STBI_rgb_alpha);
    if (!data) {
        throw std::runtime_error("stbi_load failed for " + filePath + ": " + stbi_failure_reason());
    }

    width  = static_cast<uint32_t>(w);
    height = static_cast<uint32_t>(h);

    const size_t pixelCount = width * height;
    pixels.resize(pixelCount);

    for (size_t i = 0; i < pixelCount; ++i) {
        pixels[i] = {
            static_cast<double>(data[i * 4 + 0]) / 255.0,
            static_cast<double>(data[i * 4 + 1]) / 255.0,
            static_cast<double>(data[i * 4 + 2]) / 255.0,
            static_cast<double>(data[i * 4 + 3]) / 255.0
        };
    }

    stbi_image_free(data);
}

RGBA Texture::sample(const Vector3D& uv) const {
    float u = uv.x - std::floor(uv.x);
    float v = uv.y - std::floor(uv.y);

    int x = static_cast<int>(u * width) % width;
    int y = static_cast<int>(v * height) % height;

    x = std::max(0, std::min(x, static_cast<int>(width - 1)));
    y = std::max(0, std::min(y, static_cast<int>(height - 1)));

    return pixels[y * width + x];
}

uint32_t Texture::getWidth() const {
    return width;
}
uint32_t Texture::getHeight() const {
    return height;
}