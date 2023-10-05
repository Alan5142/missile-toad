#pragma once

#include "missile_toad/core/common.hpp"

#include <LDtkLoader/Project.hpp>

namespace missiletoad::core
{

    class LdtkLoader final
    {
    public:
        /**
         * @brief Loads a room from an LDtk file.
         * @param path The path to the LDtk file.
         * @return The loaded room.
         */
        using result_type = std::shared_ptr<ldtk::Project>;

        /**
         * Loads a room from an LDtk file.
         * @param path The path to the LDtk file.
         * @return The loaded room.
         */
        result_type operator()(std::string_view path) const;
    };
} // namespace missiletoad::core
