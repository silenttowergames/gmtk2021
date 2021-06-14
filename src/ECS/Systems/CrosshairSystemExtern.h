#pragma once

#include <flecs.h>

#define CrosshairSystem_Declare() \
    CrosshairSystem_Query_Player = NULL;\
    ECS_SYSTEM(world, CrosshairSystem, EcsOnUpdate, Animate, Body, Crosshair);

#ifdef CROSSHAIRSYSTEM_FINAL
ecs_query_t* CrosshairSystem_Query_Player = NULL;
#else
extern ecs_query_t* CrosshairSystem_Query_Player;
#endif
