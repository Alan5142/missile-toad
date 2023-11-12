#pragma once
#include "common.hpp"

#include <raylib-cpp.hpp>

namespace missileengine
{
    /**
     * A wrapper around raylib::Texture that uses std::unique_ptr.
     */
    class Texture
    {
    private:
        raylib::Texture texture_;

    public:
        Texture() = default;

        ~Texture() = default;

        Texture(const Texture &)            = delete;
        Texture &operator=(const Texture &) = delete;

        Texture(Texture &&) noexcept = default;
        explicit Texture(raylib::Texture &&texture) noexcept;
        Texture &operator=(Texture &&) noexcept = default;

        /**
         * Get the underlying raylib texture.
         * @return The underlying raylib texture.
         */
        [[nodiscard]] const raylib::Texture &get_texture() const noexcept;

        /**
         * Get the underlying raylib texture.
         * @return The underlying raylib texture.
         */
        [[nodiscard]] raylib::Texture &get_texture() noexcept;

        /**
         * Set the underlying raylib texture.
         * @param texture The new underlying raylib texture.
         */
        void set_texture(raylib::Texture &&texture) noexcept;

        /**
         * Update the texture with new pixel data.
         * @param pixels The new pixel data.
         */
        void update_texture(const uint8_t *pixels) noexcept;
    };
} // namespace missileengine
