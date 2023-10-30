/// @file missile_toad/src/core/music.cpp

#include "missile_engine/music.hpp"

missileengine::Music::Music(raylib::Music &&music, std::unique_ptr<uint8_t[]> &&buffer) noexcept
    : music_(std::move(music)), buffer_(std::move(buffer))
{
}

const raylib::Music &missileengine::Music::get_music() const noexcept
{
    return music_;
}

raylib::Music &missileengine::Music::get_music() noexcept
{
    return music_;
}

void missileengine::Music::set_music(raylib::Music &&music) noexcept
{
    this->music_ = std::move(music);
}
