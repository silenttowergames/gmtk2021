#include <math.h>
#include "CrosshairSystem.h"
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Input/MouseStateFunctions.h>
#include <STE/Input/GamepadStateFunctions.h>
#include <STE/ECS/Components/Animate.h>
#include <STE/ECS/Components/Body.h>
#include "../Components/Crosshair.h"

static float2d mousePosOld;
static float2d mousePos;
static float2d center;
static float2d stickMoveOld = { .X = 0, .Y = 0, };

void CrosshairSystem(ecs_iter_t* it)
{
    fctx();
    
    if(CrosshairSystem_Query_Player == NULL)
    {
        CrosshairSystem_Query_Player = ecs_query_new(app->world, "AIPlayer,Animate,Body");
    }
    
    //SDL_SetWindowGrab(app->renderState.window, SDL_TRUE);
    //SDL_ShowCursor(0);
    
    Animate* a = ecs_column(it, Animate, 1);
    Body* b = ecs_column(it, Body, 2);
    Crosshair* c = ecs_column(it, Crosshair, 3);
    
    center.X = app->renderState.resolution.X / 2;
    center.Y = app->renderState.resolution.Y / 2;
    
    mousePos = app->inputManager.mouseState.position;
    
    for(int i = 0; i < it->count; i++)
    {
        if(mouse(Down, RIGHTCLICK) || button(Down, 0, TRIGGER_LEFT))
        {
            a[i].nextAnimationKey = "crosshair";
        }
        else
        {
            a[i].nextAnimationKey = "crosshair-idle";
        }
        
        if(mousePos.X != mousePosOld.X || mousePos.Y != mousePosOld.Y)
        {
            b[i].position = mousePos;
            
            b[i].position.X -= center.X;
            b[i].position.Y -= center.Y;
        }
        
        if(true)
        {
            float2d stickMove = { .X = 0, .Y = 0, };
            
            if(button(Down, 0, TRIGGER_LEFT))
            {
                stickMove = (float2d){
                    .X = axis(0, STICK_RIGHT_RIGHT),
                    .Y = axis(0, STICK_RIGHT_DOWN),
                };
                
                if(fabs(stickMove.X) < 0.5f)
                {
                    stickMove.X = 0;
                }
                
                if(fabs(stickMove.Y) < 0.5f)
                {
                    stickMove.Y = 0;
                }
            }
            else
            {
                stickMove = (float2d){
                    .X = axis(0, STICK_LEFT_RIGHT),
                    .Y = axis(0, STICK_LEFT_DOWN),
                };
                
                if(fabs(stickMove.X) < 0.15f)
                {
                    stickMove.X = 0;
                }
                
                if(fabs(stickMove.Y) < 0.15f)
                {
                    stickMove.Y = 0;
                }
            }
            
            if(stickMove.X != 0 || stickMove.Y != 0)
            {
                if(button(Down, 0, TRIGGER_LEFT))
                {
                    b[i].position.X = stickMove.X * 3;
                    b[i].position.Y = stickMove.Y * 3;
                }
                else
                {
                    b[i].position.X += stickMove.X * 3;
                    b[i].position.Y += stickMove.Y * 3;
                }
            }
            
            stickMoveOld = stickMove;
        }
        
        float rotation = atan2(b[i].position.X, b[i].position.Y);
        
        b[i].position.X = sinf(rotation) * 64;
        b[i].position.Y = cosf(rotation) * 64;
        
        b[i].position.X = roundf(b[i].position.X);
        b[i].position.Y = roundf(b[i].position.Y);
    }
    
    mousePosOld = mousePos;
}
