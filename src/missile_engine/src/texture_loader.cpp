/// @file missile_toad/src/core/texture_loader.cpp

#include "missile_engine/texture_loader.hpp"
#include <gsl/gsl>
#include <physfs.h>

missileengine::TextureLoader::result_type missileengine::TextureLoader::operator()(std::string_view name) const
{
    // Load the data.
    auto data_opt = load_file(name);
    if (!data_opt.has_value())
    {
        spdlog::error("Failed to load texture");
        throw std::runtime_error("Failed to load texture");
    }
    spdlog::trace("Loaded texture from {}", name);

    auto &[data, size] = data_opt.value();
    // Get file extension (including .)
    std::string_view extension = name.substr(name.find_last_of('.'));

    spdlog::trace("Texture has extension {}", extension);

    // Load the texture from memory
    auto texture = LoadImageFromMemory(extension.data(), data.get(), static_cast<int>(size));

    // Check if the texture was loaded correctly
    if (texture.data == nullptr)
    {
        spdlog::error("Failed to load texture");
        throw std::runtime_error("Failed to load texture");
    }
    spdlog::trace("Loaded texture from memory");

    // Generate the texture
    auto texture_ptr = raylib::Texture(LoadTextureFromImage(texture));
    spdlog::info("Loaded texture to GPU");

    // Unload the image
    UnloadImage(texture);

    // Return the texture
    return std::make_shared<Texture>(std::move(texture_ptr));
}
