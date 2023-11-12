#pragma once
#include "common.hpp"

#include <glm/vec2.hpp>
#include <pl_mpeg/pl_mpeg.h>
#include <raylib-cpp.hpp>

namespace missileengine
{
    /**
     * @brief Allows to play a mpeg movie.
     * It requires a SpriteComponent to be attached to the entity to render the movie.
     */
    class Movie
    {
    public:
        /**
         * @brief Construct a new Movie object
         * @param movie The movie to wrap.
         */
        Movie(plm_t *movie, std::unique_ptr<uint8_t[]> &&video_buffer);

        ~Movie();

        Movie(const Movie &)            = delete;
        Movie &operator=(const Movie &) = delete;

        Movie(Movie &&) noexcept;
        Movie &operator=(Movie &&) noexcept;

        void play();

        void pause();

        void seek(std::chrono::milliseconds time);

        void update(float delta_time);

        [[nodiscard]] const raylib::Texture &get_texture() const noexcept
        {
            return texture_;
        }

        [[nodiscard]] glm::u32vec2 get_size() const noexcept
        {
            return size_;
        }

    private:
        static void decode_video(plm_t *self, plm_frame_t *frame, void *user_data);
        static void decode_audio(plm_t *self, plm_samples_t *samples, void *user_data);

        std::unique_ptr<uint8_t[]> video_buffer_;
        raylib::Texture            texture_;
        raylib::Image              image_;
        // raylib::AudioStream        audio_stream_;

        plm_t       *movie_;
        glm::u32vec2 size_;
        bool         playing_;

        friend class MoviePlayerSystem;
    };
} // namespace missileengine
