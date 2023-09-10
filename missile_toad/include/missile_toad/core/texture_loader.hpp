#pragma once

#include "common.hpp"
#include "texture.hpp"

namespace missiletoad::core
{
    class TextureLoader final
    {
    public:
        using result_type = std::shared_ptr<Texture>;

        result_type operator()(std::string_view name) const;
    };
} // namespace missiletoad::core