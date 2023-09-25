#include "missile_toad/core/scene_descriptor.hpp"
#include "missile_toad/core/schema_includes.hpp"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

std::optional<missiletoad::core::SceneDescriptor> missiletoad::core::load_scene_descriptor(std::string_view path)
{
    auto scene_content = load_file(path);

    if (!scene_content.has_value())
    {
        spdlog::trace("Failed to load scene descriptor: {}", path);
        return std::nullopt;
    }

    rapidjson::Document document;
    auto &[data, size] = scene_content.value();
    // NOLINTNEXTLINE(*-pro-type-reinterpret-cast)
    document.Parse(reinterpret_cast<const char *>(data.get()));

    if (document.HasParseError())
    {
        spdlog::trace("Failed to parse scene descriptor: {}", path);
        return std::nullopt;
    }

    SceneDescriptor scene_descriptor;
    scene_descriptor.name = document["name"].GetString();

    for (const auto &system : document["systems"].GetArray())
    {
        scene_descriptor.systems.emplace_back(system.GetString());
    }

    return scene_descriptor;
}
