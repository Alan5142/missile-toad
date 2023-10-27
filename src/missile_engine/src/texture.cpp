/// @file missile_toad/src/core/texture.cpp

#include "missile_engine/texture.hpp"

missilengine::Texture::Texture(raylib::Texture &&texture) noexcept : texture_(std::move(texture))
{
}

const raylib::Texture &missilengine::Texture::get_texture() const noexcept
{
    return texture_;
}

raylib::Texture &missilengine::Texture::get_texture() noexcept
{
    return texture_;
}

void missilengine::Texture::set_texture(raylib::Texture &&texture) noexcept
{
    this->texture_ = std::move(texture);
}
