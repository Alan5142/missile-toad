#include "missile_toad/core/texture_loader.hpp"
#include <gsl/gsl>
#include <physfs.h>

missiletoad::core::TextureLoader::result_type missiletoad::core::TextureLoader::operator()(std::string_view name) const
{
    // Load the data.
    auto data_opt = load_file(name);
    if (!data_opt.has_value())
    {
        spdlog::error("Failed to load texture");
        throw std::runtime_error("Failed to load texture");
    }

    auto &[data, size] = data_opt.value();
    // Get file extension (including .)
    std::string_view extension = name.substr(name.find_last_of('.'));

    // Load the texture from memory
    auto texture = LoadImageFromMemory(extension.data(), data.get(), static_cast<int>(size));

    // Check if the texture was loaded correctly
    if (texture.data == nullptr)
    {
        spdlog::error("Failed to load texture");
        throw std::runtime_error("Failed to load texture");
    }

    // Generate the texture
    auto texture_ptr = std::make_unique<raylib::Texture>(LoadTextureFromImage(texture));

    // Unload the image
    UnloadImage(texture);

    // Return the texture
    return std::make_shared<Texture>(std::move(texture_ptr));
}