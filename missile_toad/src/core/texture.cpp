/// @file missile_toad/src/core/texture.cpp

#include "missile_toad/core/texture.hpp"

missiletoad::core::Texture::Texture(raylib::Texture &&texture) noexcept : texture_(std::move(texture))
{
}

const raylib::Texture &missiletoad::core::Texture::get_texture() const noexcept
{
    return texture_;
}

raylib::Texture &missiletoad::core::Texture::get_texture() noexcept
{
    return texture_;
}

void missiletoad::core::Texture::set_texture(raylib::Texture &&texture) noexcept
{
    this->texture_ = std::move(texture);
}
