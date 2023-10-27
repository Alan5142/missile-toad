#pragma once
#include "missile_engine/common.hpp"

namespace missilengine::schemas
{
    constexpr std::string_view COMPONENT = R"({
  "$id": "https://missile-toad.com/schemas/component.json",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "Entity",
  "description": "An entity in the game world.",
  "type": "object",
  "properties": {
    "class": {
      "description": "The class of the entity. Must be reflected and provide a parameterless constructor.",
      "type": "string"
    },
    "args": {
      "description": "The arguments to pass to the component.",
      "type": "array",
      "items": {
        "type": "object",
        "properties": {
          "name": {
            "description": "The name of the argument.",
            "type": "string"
          },
          "value": {
            "description": "The value of the argument.",
            "type": "any"
          }
        }
      }
    }
  }
}
)";
    constexpr std::string_view ENTITY    = R"({
  "$id": "https://missile-toad.com/schemas/entity.json",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "Entity",
  "description": "An entity in the game world.",
  "type": "object",
  "properties": {
    "components": {
      "type": "array",
      "items": {
        "$ref": "https://missile-toad.com/schemas/component.json"
      }
    }
  }
}
)";
    constexpr std::string_view GAME      = R"({
  "$id": "https://missile-toad.com/schemas/game.json",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "Game Definition",
  "description": "Defines options for a game.",
  "type": "object",
  "properties": {
    "name": {
      "description": "The name of the game.",
      "type": "string"
    },
    "assets": {
      "description": "The asset folder for the game.",
      "type": "array",
      "items": {
        "type": "object",
        "required": [
          "path",
          "mount"
        ],
        "properties": {
          "path": {
            "description": "The path to the asset folder.",
            "type": "string"
          },
          "mount": {
            "description": "The mount point for the asset folder.",
            "type": "string"
          }
        }
      }
    },
    "defaultScene": {
      "description": "The default scene to load when the game starts.",
      "type": "string"
    }
  },
  "required": [
    "assets",
    "name",
    "defaultScene"
  ]
}
)";
    constexpr std::string_view SCENE     = R"({
  "$id": "https://missile-toad.com/schemas/scene.json",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "Scene",
  "description": "A scene in a game.",
  "type": "object",
  "properties": {
    "name": {
      "description": "The name of the scene.",
      "type": "string"
    },
    "systems": {
      "description": "The systems in the scene.",
      "type": "array",
      "items": {
        "$ref": "system.json"
      }
    },
    "entities": {
      "description": "The objects in the scene.",
      "type": "array",
      "items": {
        "$ref": "entity.json"
      }
    }
  }
}
)";
    constexpr std::string_view SYSTEM    = R"({
  "$id": "https://missile-toad.com/schemas/scene.json",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "title": "System",
  "description": "An ECS system to run",
  "type": "object",
  "properties": {
    "class": {
      "type": "string",
      "description": "The class name of the system to run"
    },
    "priority": {
      "type": "integer",
      "description": "The priority of the system to run, lower numbers run first, starting at 0"
    }
  }
}
)";
} // namespace missilengine::schemas
