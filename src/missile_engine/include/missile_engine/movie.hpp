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

        Movie(Movie &&other) noexcept;
        Movie &operator=(Movie &&other) noexcept;

        /**
         * @brief Plays the movie.
         */
        void play();

        /**
         * @brief Pauses the movie.
         */
        void pause();

        /**
         * @brief Seek to a specific time.
         * @param time The time to seek to.
         */
        void seek(std::chrono::milliseconds time);

        /**
         * @brief Updates the movie, decoding the video and audio to the buffers.
         * @param delta_time The delta time.
         */
        void update(float delta_time);

        /**
         * @brief Gets the texture of the movie.
         * @return The texture of the movie.
         */
        [[nodiscard]] const raylib::Texture &get_texture() const noexcept
        {
            return texture_;
        }

        /**
         * @brief Gets the size of the movie.
         * @return The size of the movie.
         */
        [[nodiscard]] glm::u32vec2 get_size() const noexcept
        {
            return size_;
        }

    private:
        /**
         * Handles the decoding of the video.
         * @param self pointer to the movie
         * @param frame the frame
         * @param user_data user data (pointer to this)
         */
        static void decode_video(plm_t *self, plm_frame_t *frame, void *user_data);

        /**
         * Handles the decoding of the audio.
         * @param self pointer to the movie
         * @param samples the samples
         * @param user_data user data (pointer to this)
         */
        static void decode_audio(plm_t *self, plm_samples_t *samples, void *user_data);

        /**
         * @brief The memory buffer of the video.
         */
        std::unique_ptr<uint8_t[]> video_buffer_;

        /**
         * @brief the texture of the movie, this is what gets rendered.
         */
        raylib::Texture texture_;

        /**
         * @brief A CPU bound image, used to decode the video. This is copied to the texture.
         */
        raylib::Image image_;
        // raylib::AudioStream        audio_stream_;

        /**
         * @brief decoder for the movie.
         */
        plm_t *movie_;

        /**
         * @brief The size of the movie.
         */
        glm::u32vec2 size_;

        /**
         * @brief Wether the movie is playing or not.
         */
        bool playing_{false};

        friend class MoviePlayerSystem;
    };
} // namespace missileengine
