#include <stdlib.h>
#include <STE/Assets/AssetManagerFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/RenderableFunctions.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Utilities/colorFunctions.h>

#include "../../ecs_declarations.h"
#include "NPCFactory.h"
#include "../Components/AINPC.h"

ecs_entity_t NPCFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
	ctx();
    
    X -= 4;
    Y -= 12;
	
    ecs_entity_t f = ecs_new(world, 0);
    
    ecs_set(world, f, AINPC, {
        0.25f,
    });
    ecs_set(world, f, Animate, {
        "man-die",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, f, BasicAABB, BasicAABB_Create(1, Hitbox_CreateSquare(8)));
    ecs_set(world, f, Body, bodyEasy(X, Y));
    ecs_set(world, f, Renderable, RenderableSprite(
        getTexture("8x8"),
        int2dInit(0, 0),
        layer,
        (rand() % 10) / 10.0f,
        1,
        0xFFFFFFFF,
        0
    ));
    
    return f;
}
