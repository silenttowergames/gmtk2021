#pragma once

#include <flecs.h>
#include <STE/Assets/TiledJSONObject.h>

ecs_entity_t TextBoxFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object);
