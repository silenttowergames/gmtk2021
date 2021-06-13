#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/ECS/Components/Body.h>
#include <STE/ECS/Components/Renderable.h>
#include "FlipSpritesSystem.h"

void FlipSpritesSystem(ecs_iter_t* it)
{
    fctx();
    
    Body* b = ecs_column(it, Body, 1);
    Renderable* r = ecs_column(it, Renderable, 2);
    
    for(int i = 0; i < it->count; i++)
    {
        if(b[i].effectiveVelocity.X == 0)
        {
            continue;
        }
        
        if(b[i].effectiveVelocity.X > 0)
        {
            r[i].flipX = false;
        }
        
        if(b[i].effectiveVelocity.X < 0)
        {
            r[i].flipX = true;
        }
    }
}