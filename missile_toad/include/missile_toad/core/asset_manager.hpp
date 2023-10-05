#pragma once
#include "common.hpp"
#include "ldtk_loader.hpp"
#include "music_loader.hpp"
#include "texture_loader.hpp"

#include <entt/core/hashed_string.hpp>
#include <entt/resource/cache.hpp>
#include <unordered_map>

#include <raylib-cpp.hpp>

namespace missiletoad::core
{
    class AssetManager
    {
    private:
        entt::resource_cache<Texture, TextureLoader>    texture_cache_;
        entt::resource_cache<Music, MusicLoader>        music_cache_;
        entt::resource_cache<ldtk::Project, LdtkLoader> ldtk_cache_;

    public:
        AssetManager();
        ~AssetManager();

        AssetManager(const AssetManager &)            = delete;
        AssetManager &operator=(const AssetManager &) = delete;

        AssetManager(AssetManager &&)            = delete;
        AssetManager &operator=(AssetManager &&) = delete;

        /**
         * Pushes an asset folder to the stack.
         * @param path Path to the folder.
         * @param mount_point The mount point for the folder.
         */
        void push_asset_folder(std::string_view path, std::string_view mount_point);

        /**
         * Pops an asset folder from the stack.
         */
        void pop_asset_folder(std::string_view mount_point);

        // GCC has a bug that prevents template specializations in non-namespace scope.
        // See: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85282
        // Workaround is to use partial specializations with std::same_as.

        /**
         * Dummy load function that will fail to compile if the type is not supported.
         */
        template <typename T>
        entt::resource<T> load(std::string_view name)
        {
            unused(name);
            static_assert("Asset type not supported");
        }

        /**
         * Loads a texture.
         * @tparam T Texture
         * @param name The name of the texture in the filesystem.
         * @return The texture.
         */
        template <std::same_as<Texture> T>
        entt::resource<T> load(std::string_view name)
        {
            return texture_cache_.load(entt::hashed_string{name.data()}, name.data()).first->second;
        }

        /**
         * Loads a music track.
         * @tparam T Music
         * @param name The name of the music in the filesystem.
         * @return The music.
         */
        template <std::same_as<Music> T>
        entt::resource<T> load(std::string_view name)
        {
            return music_cache_.load(entt::hashed_string{name.data()}, name.data()).first->second;
        }

        /**
         * Loads an LDtk project.
         * @tparam T LDtk project
         * @param name The name of the LDtk project in the filesystem.
         * @return The LDtk project.
         */
        template <std::same_as<ldtk::Project> T>
        entt::resource<T> load(std::string_view name)
        {
            return ldtk_cache_.load(entt::hashed_string{name.data()}, name.data()).first->second;
        }
    };
} // namespace missiletoad::core
