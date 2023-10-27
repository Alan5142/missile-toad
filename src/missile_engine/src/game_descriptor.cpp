#include "missile_engine/game_descriptor.hpp"
#include "missile_engine/schema_includes.hpp"

#include "rapidjson/document.h"
#include "rapidjson/schema.h"

std::optional<missilengine::GameDescriptor> missilengine::load_game_descriptor(std::string_view descriptor)
{
    // Use Schema
    rapidjson::Document schema_document;
    schema_document.Parse(schemas::GAME.data());

    rapidjson::SchemaDocument schema(schema_document);

    rapidjson::Document document;
    document.Parse(descriptor.data());

    rapidjson::SchemaValidator validator(schema);

    if (!document.Accept(validator))
    {
        rapidjson::StringBuffer buffer;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(buffer);
        spdlog::trace("Invalid schema: {}", buffer.GetString());
        spdlog::trace("Invalid keyword: {}", validator.GetInvalidSchemaKeyword());
        buffer.Clear();
        validator.GetInvalidDocumentPointer().StringifyUriFragment(buffer);
        spdlog::trace("Invalid document: {}", buffer.GetString());
        return std::nullopt;
    }
    auto game_descriptor = missilengine::GameDescriptor();

    game_descriptor.name          = document["name"].GetString();
    game_descriptor.default_scene = document["defaultScene"].GetString();
    game_descriptor.assets_folders.reserve(document["assets"].Size());

    for (const auto &folder : document["assets"].GetArray())
    {
        game_descriptor.assets_folders.push_back(missilengine::PathFolder{
            .path        = folder["path"].GetString(),
            .mount_point = folder["mount"].GetString(),
        });
    }

    return game_descriptor;
}
