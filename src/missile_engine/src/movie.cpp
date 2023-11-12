#include <cstddef>

#include "missile_engine/movie.hpp"

missileengine::Movie::Movie(plm_t *movie, std::unique_ptr<uint8_t[]> &&video_buffer)
    : video_buffer_(std::move(video_buffer)), movie_(movie), playing_(false)
{
    size_ = {plm_get_width(movie_), plm_get_height(movie_)};
    plm_set_loop(movie_, 1);

    // plm_set_audio_stream(movie_, 0);

    plm_set_video_decode_callback(movie_, &Movie::decode_video, this);
    // plm_set_audio_decode_callback(movie_, &Movie::decode_audio, this);

    // const auto sample_rate = plm_get_samplerate(movie_);

    // audio_stream_.SetBuffer(nullptr);

    // audio_stream_ = LoadAudioStream(sample_rate, 32, 2);

    // audio_stream_.Play();

    // plm_set_audio_lead_time(movie_, PLM_AUDIO_SAMPLES_PER_FRAME / sample_rate);
    plm_set_audio_enabled(movie_, 0);

    auto *image_buffer = malloc(size_.x * size_.y * 3 * sizeof(uint8_t));
    image_             = raylib::Image(image_buffer, size_.x, size_.y, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8);

    texture_ = raylib::Texture(image_);
}

void missileengine::Movie::decode_video(plm_t *self, plm_frame_t *frame, void *user_data)
{
    unused(self);
    auto *movie = static_cast<Movie *>(user_data);
    plm_frame_to_rgb(frame, static_cast<uint8_t *>(movie->image_.GetData()), static_cast<int>(movie->size_.x * 3));
}

void missileengine::Movie::decode_audio(plm_t *self, plm_samples_t *samples, void *user_data)
{
    unused(self, samples, user_data);
    // auto *movie = static_cast<Movie *>(user_data);
    // while (movie->audio_stream_.IsProcessed())
    // {
    //     movie->audio_stream_.Update(samples->interleaved, samples->count);
    // }
}

missileengine::Movie::~Movie()
{
    if (movie_ != nullptr)
    {
        plm_destroy(movie_);
    }
}

missileengine::Movie::Movie(Movie &&other) noexcept : movie_(other.movie_), playing_(other.playing_)
{
    other.movie_ = nullptr;
}

missileengine::Movie &missileengine::Movie::operator=(Movie &&other) noexcept
{
    if (this != &other)
    {
        if (movie_ != nullptr)
        {
            plm_destroy(movie_);
        }
        movie_       = other.movie_;
        other.movie_ = nullptr;
    }
    return *this;
}

void missileengine::Movie::play()
{
    playing_ = true;
}

void missileengine::Movie::pause()
{
    playing_ = false;
}

void missileengine::Movie::seek(std::chrono::milliseconds time)
{
    const auto double_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(time);
    plm_seek(movie_, double_seconds.count(), static_cast<int>(false));
}

void missileengine::Movie::update(float delta_time)
{
    if (playing_)
    {
        plm_decode(movie_, delta_time);
    }
}
