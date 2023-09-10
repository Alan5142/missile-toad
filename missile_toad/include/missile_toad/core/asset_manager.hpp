#pragma once
#include "common.hpp"

#include <unordered_map>

#include "raylib-cpp.hpp"

namespace missiletoad::core
{
    class AssetManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<raylib::Texture>> textures;
        std::unordered_map<std::string, std::shared_ptr<raylib::Sound>>   sounds;
        std::unordered_map<std::string, std::shared_ptr<raylib::Music>>   music;
        std::unordered_map<std::string, std::shared_ptr<raylib::Font>>    fonts;

    public:
        AssetManager();
        ~AssetManager();

        AssetManager(const AssetManager &)            = delete;
        AssetManager &operator=(const AssetManager &) = delete;

        AssetManager(AssetManager &&)            = delete;
        AssetManager &operator=(AssetManager &&) = delete;

        /**
         * Get a texture from the asset manager. If the texture is not loaded, it will be loaded.
         * @param name Path to the texture in the VFS.
         * @return A shared pointer to the texture.
         */
        std::shared_ptr<raylib::Texture> get_texture(std::string_view name);

        /**
         * Get a sound from the asset manager. If the sound is not loaded, it will be loaded.
         * @param name Path to the sound in the VFS.
         * @return A shared pointer to the sound.
         */
        std::shared_ptr<raylib::Sound> get_sound(std::string_view name);

        /**
         * Get a music from the asset manager. If the music is not loaded, it will be loaded.
         * @param name Path to the music in the VFS.
         * @return A shared pointer to the music.
         */
        std::shared_ptr<raylib::Music> get_music(std::string_view name);

        /**
         * Get a font from the asset manager. If the font is not loaded, it will be loaded.
         * @param name Path to the font in the VFS.
         * @return A shared pointer to the font.
         */
        std::shared_ptr<raylib::Font> get_font(std::string_view name);

    private:
        /**
         * Load a file from the VFS.
         * @param name Path to the file in the VFS.
         * @return A vector of bytes containing the file.
         */
        static std::vector<std::byte> load_file(std::string_view name);
    };
} // namespace missiletoad::core
