#pragma once

#include "missile_engine/common.hpp"

#include <LDtkLoader/Project.hpp>

namespace missileengine
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
} // namespace missileengine
