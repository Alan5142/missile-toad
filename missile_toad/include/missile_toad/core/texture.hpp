#pragma once
#include "common.hpp"

#include <raylib-cpp.hpp>

namespace missiletoad::core
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
    };
} // namespace missiletoad::core
