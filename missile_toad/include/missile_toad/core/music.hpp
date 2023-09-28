#pragma once
#include "common.hpp"

#include <raylib-cpp.hpp>

namespace missiletoad::core
{
    /**
     * A wrapper around raylib::Music that uses std::unique_ptr.
     */
    class Music
    {
    private:
        raylib::Music              music_;
        std::unique_ptr<uint8_t[]> buffer_;

    public:
        ~Music() = default;

        Music(const Music &)            = delete;
        Music &operator=(const Music &) = delete;

        Music(Music &&) noexcept = default;
        Music(raylib::Music &&music, std::unique_ptr<uint8_t[]> &&buffer) noexcept;
        Music &operator=(Music &&) noexcept = default;

        /**
         * Get the underlying raylib music.
         * @return The underlying raylib music.
         */
        [[nodiscard]] const raylib::Music &get_music() const noexcept;

        /**
         * Get the underlying raylib music.
         * @return The underlying raylib music.
         */
        [[nodiscard]] raylib::Music &get_music() noexcept;

        /**
         * Set the underlying raylib music.
         * @param music The new underlying raylib music.
         */
        void set_music(raylib::Music &&music) noexcept;
    };
} // namespace missiletoad::core
