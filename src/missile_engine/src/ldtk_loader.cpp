
#include "missile_engine/ldtk_loader.hpp"

missilengine::LdtkLoader::result_type missilengine::LdtkLoader::operator()(std::string_view path) const
{
    // Load the data.
    auto data_opt = load_file(path);
    if (!data_opt.has_value())
    {
        spdlog::error("Failed to load level");
        throw std::runtime_error("Failed to load level");
    }
    spdlog::trace("Loaded level from {}", path);

    auto &[data, size] = data_opt.value();

    // Load the level
    auto level = std::make_shared<ldtk::Project>();
    level->loadFromMemory(data.get(), static_cast<unsigned int>(size));
    spdlog::info("Loaded level");

    // Return the level
    return level;
}
