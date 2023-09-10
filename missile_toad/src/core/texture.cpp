#include "missile_toad/core/texture.hpp"

missiletoad::core::Texture::Texture(std::unique_ptr<raylib::Texture> &&texture) noexcept : texture_(std::move(texture))
{
}

raylib::Texture &missiletoad::core::Texture::get_texture() const noexcept
{
    return *texture_;
}

void missiletoad::core::Texture::set_texture(std::unique_ptr<raylib::Texture> texture) noexcept
{
    this->texture_ = std::move(texture);
}
