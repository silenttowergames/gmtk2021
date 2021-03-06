#include <STE/StoneTower.h>
#include <STE/includes_libs.h>
#include <STE/includes_vendor.h>
#include "ecs_declarations.h"
#include <STE/includes.h>
#include "includes.h"

ECS_Setup(DECLARE, );

void initWorld(ecs_world_t* world)
{
    ECS_Setup(DEFINE, world);
    
    ECS_SYSTEM(world, FPSPrintSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, FullscreenShortcutSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, PauseMenuSystem, EcsOnUpdate, Menu, PauseMenu);
    ECS_SYSTEM(world, AINPCSystem, EcsOnUpdate, AINPC, Body);
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, AIPlayer, Body);
    
    BasicAABBSystem_Init();
    
    MenuSystem_Init();
    
    DebugMovableSystem_Init();
    
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow, Renderable);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    
    CrosshairSystem_Declare();
    
    ECS_SYSTEM(world, FlipSpritesSystem, EcsOnUpdate, Body, Renderable);
    
    DrawSystem_Init();
}

int main(int arcg, char* argv[])
{
    configDefault(config, 1280 * 2, 720 * 2, "en", true);
    
    init(
        "GMTK 2021: The Butterfly Effect",
        "v1.0.0",
        "OpenGL",
        60,
        config,
        320, 180,
        1024, 1024,
        initWorld,
        "map0",
        RSZ_Floor
    );
    
    gameDataInit(
        3,
        gdAttr("Integers", "hello", 27, Int),
        gdAttr("Integers", "hiThere", 8, Int),
        gdAttr("Strings", "alrighty", "Well! Hello.", String)
    );
    
    scenes(
        4,
        scene(initialize),
        sceneTiled("map1", init2Scene),
        sceneTiled("map0", NULL),
        scene(init2)
    );
    
    textures(
        3,
        Texture_Create(&app, "gmtk-2021-16x16", 16, 16, 0, 0, 0, 0),
        Texture_Create(&app, "16x16", 16, 16, 0, 0, 0, 0),
        Texture_Create(&app, "8x8", 8, 8, 0, 0, 0, 0)
    );
    
    maps(
        2,
        TiledJSON_Load(&app, "map0"),
        TiledJSON_Load(&app, "map1")
    );
    
    shaders(
        2,
        Shader_Create(&app, "CRTShader", ShaderUpdate_Disable),
        Shader_Create(&app, "YellowShader", NULL)
    );
    
    scripts(
        2,
        LuaScript_Load(&app, "test"),
        LuaScript_Load(&app, "test2")
    );
    
    fonts(
        2,
        Font_Create(&app, "Bloodyslime/Bloodyslime.ttf"),
        Font_Create(&app, "PressStart2P/PressStart2P.ttf")
    );
    
    sounds(
        4,
        Sound_create_load("calm-example.ogg", Play_StopAll, SoundCategory_Music),
        Sound_create_load("hit.ogg", Play_StopOne, SoundCategory_SFX),
        Sound_create_speech(
            "speech0",
            "the destruction that way steth at noonday.",
            Play_Default,
            SoundCategory_SFX
        ),
        Sound_create_sfxr("sfxr", Play_Default, SoundCategory_SFX)
    );
    
    factories(
        5,
        factory(Bullet),
        factory(Player),
        factory(NPC),
        factory(TextBox),
        factory(TestMenu)
    );
    
    renderTargets(
        1,
        RenderTarget_Create(&app, (int2d){ 320, 180, }, (int2d){ 320, 180, }, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 1, 0, 1, 1, })
        //RenderTarget_Create(&app, (int2d){ 80, 80, }, (int2d){ 80, 80, }, (int2d){ 40, 40, }, false, (FNA3D_Vec4){ 1, 1, 1, 0.5f, })
    );
    
    //*
    app.renderState.targets[0].shadersCount = 1;
    app.renderState.targets[0].shaders = malloc(sizeof(Shader*) * app.renderState.targets[0].shadersCount);
    app.renderState.targets[0].shaders[0] = *mapGet(app.assetManager.mapShader, "YellowShader", Shader*);
    app.renderState.mainRenderTarget.shadersCount = 1;
    app.renderState.mainRenderTarget.shaders = malloc(sizeof(Shader*) * app.renderState.mainRenderTarget.shadersCount);
    app.renderState.mainRenderTarget.shaders[0] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //app.renderState.mainRenderTarget.shaders[1] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //*/
    
    ConsoleCommand_AddAll(
        &app,
        9,
        ConsoleCommand_Create("exit", cmdExit),
        ConsoleCommand_Create("play", cmdPlaySound),
        ConsoleCommand_Create("volume", cmdVolume),
        ConsoleCommand_Create("scene", cmdChangeScene),
        ConsoleCommand_Create("pause", cmdPause),
        ConsoleCommand_Create("unpause", cmdUnpause),
        ConsoleCommand_Create("website", cmdWebsite),
        ConsoleCommand_Create("reload-map", cmdReloadMap),
        ConsoleCommand_Create("movable", cmdMovable)
    );
    
    loop();
    
    GameData_Save(&app.gameData);
    
    quit();
}
