/// @file missile_toad/src/core/texture_loader.cpp

#include "missile_engine/music_loader.hpp"
#include <gsl/gsl>
#include <physfs.h>

missileengine::MusicLoader::result_type missileengine::MusicLoader::operator()(std::string_view name) const
{
    // Load the data.
    auto data_opt = load_file(name);
    if (!data_opt.has_value())
    {
        spdlog::error("Failed to load music");
        throw std::runtime_error("Failed to load music");
    }
    spdlog::trace("Loaded music from {}", name);

    auto &[data, size] = data_opt.value();
    // Get file extension (including .)
    std::string_view extension = name.substr(name.find_last_of('.'));

    spdlog::trace("Music has extension {}", extension);

    // Load the texture from memory
    auto music = LoadMusicStreamFromMemory(extension.data(), data.get(), static_cast<int>(size));

    // Check if the texture was loaded correctly
    if (music.stream.buffer == nullptr) // Probable punto de falla xd
    {
        spdlog::error("Failed to load music");
        throw std::runtime_error("Failed to load music");
    }
    spdlog::trace("Loaded music from memory");

    return std::make_shared<Music>(music, std::move(data));
}
