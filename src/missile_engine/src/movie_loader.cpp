#include "missile_engine/movie_loader.hpp"

#include <pl_mpeg/pl_mpeg.h>

missileengine::MovieLoader::result_type missileengine::MovieLoader::operator()(std::string_view name) const
{
    // Load the data.
    auto data_opt = load_file(name);
    if (!data_opt.has_value())
    {
        spdlog::error("Failed to load the movie");
        throw std::runtime_error("Failed to load the movie");
    }
    spdlog::trace("Loaded movie from {}", name);

    auto &[data, size] = data_opt.value();

    auto *plm_buffer = plm_buffer_create_with_memory(data.get(), size, 0);
    auto *movie      = plm_create_with_buffer(plm_buffer, 0);

    return std::make_shared<missileengine::Movie>(movie, std::move(data));
}
