#include <flecs.h>
#include "MoveSystem.h"
#include <STE/ECS/FlecsMapFunctions.h>
#include <STE/Application/ApplicationState.h>
#include <STE/ECS/FlecsFunctions.h>
#include <STE/ECS/Components/BasicAABB.h>
#include <STE/ECS/Components/Body.h>
#include <STE/Audio/SoundFunctions.h>
#include <STE/Application/ConfigFunctions.h>
#include <STE/Application/ApplicationStateFunctions.h>
#include <STE/Input/GamepadStateFunctions.h>
#include <STE/Input/KeyboardStateFunctions.h>
#include <STE/Input/MouseStateFunctions.h>
#include <STE/Utilities/wallsFunctions.h>
#include <STE/GameData/GameDataAttribute.h>
#include <STE/GameData/GameDataFunctions.h>

#include "../Components/AIPlayer.h"

void MoveSystem(ecs_iter_t* it)
{
	fctx();
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		memset(&b[i].velocity, 0, sizeof(float2d));
		
		if(keys(Down, RIGHT) || keys(Down, d) || button(Down, 0, DPAD_RIGHT) || button(Down, 0, STICK_LEFT_RIGHT))
		{
			b[i].velocity.X += a[i].speed;
		}
		
		if(keys(Down, LEFT) || keys(Down, a) || button(Down, 0, DPAD_LEFT) || button(Down, 0, STICK_LEFT_LEFT))
		{
			b[i].velocity.X -= a[i].speed;
		}
		
		if(keys(Down, DOWN) || keys(Down, s) || button(Down, 0, DPAD_DOWN) || button(Down, 0, STICK_LEFT_DOWN))
		{
			b[i].velocity.Y += a[i].speed;
		}
		
		if(keys(Down, UP) || keys(Down, w) || button(Down, 0, DPAD_UP) || button(Down, 0, STICK_LEFT_UP))
		{
			b[i].velocity.Y -= a[i].speed;
		}
	}
}
