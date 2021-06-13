#include "BulletFactory.h"
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>
#include "../../ecs_declarations.h"

ecs_entity_t BulletFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, Animate, {
        "bullet",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, e, BasicAABB, BasicAABB_Create(1, Hitbox_CreateSquare(2)));
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, Renderable, RenderableSprite(
        getTexture("gmtk-2021-16x16"),
        int2dInit(0, 0),
        layer,
        0.5f,
        1,
        0xFFFFFFFF,
        0
    ));
    
    return e;
}
