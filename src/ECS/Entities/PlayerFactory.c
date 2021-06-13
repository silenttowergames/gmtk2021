#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/CameraFollow.h>
#include <STE/ECS/Components/RenderableFunctions.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/Assets/TiledJSONObject.h>
#include <STE/Assets/TiledJSONProperty.h>
#include <STE/Application/ApplicationStateFunctions.h>

#include "../../ecs_declarations.h"
#include "PlayerFactory.h"
#include "../Components/AIPlayer.h"
#include "../Components/Crosshair.h"

ecs_entity_t PlayerFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    // Example of using properties
    TiledJSONProperty* prop = getProperty(object, "modify");
    if(prop != NULL && prop->valueBool)
    {
        X += 32;
    }
    
    ecs_set(world, e, AIPlayer, {
        1.0f,
    });
    ecs_set(world, e, Animate, {
        "protag-walk",
        NULL,
        0,
        0,
        1.0f,
    });
    
    Hitbox h = Hitbox_CreateSquare(8);
    h.offset.Y = 2;
    
    ecs_set(world, e, BasicAABB, BasicAABB_Create(1, h));
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, CameraFollow, {
        { 0, 0, },
    });
    ecs_set(world, e, Renderable, RenderableSprite(
        getTexture("gmtk-2021-16x16"),
        int2dInit(0, 0),
        layer,
        0.5f,
        1,
        0xFFFFFFFF,
        0
    ));
    
    ecs_entity_t c = ecs_new(world, 0);
    
    ecs_set(world, c, Animate, {
        "crosshair-idle",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, c, Body, bodyEasy(X + 32, Y + 32));
    ecs_set(world, c, Crosshair, { .id = e, });
    ecs_set(world, c, Renderable, RenderableSprite(
        getTexture("gmtk-2021-16x16"),
        int2dInit(0, 0),
        layer + 10,
        0.5f,
        0,
        0xFFFFFFFF,
        0
    ));
    
    return e;
}
