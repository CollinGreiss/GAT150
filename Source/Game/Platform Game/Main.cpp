#include <iostream>

#include "Core/Memory.h"
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"

#include "PlatformGame.h"

using namespace std;
using namespace kiko;

int main(int argc, char* argv[]) {

    INFO_LOG("Initializing Game Engine...");

    MemoryTracker::Initialize();

    /////Setup

    seedRandom((unsigned int)time(nullptr));
    setFilePath("assets");

    g_renderer.Initialize();
    g_renderer.CreateWindow("GAT150", 1920, 1056);

    g_inputSystem.Initialize();
    g_audioSystem.Initialize();
    PhysicsSystem::Instance().Initialize();

    unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
    game->Initialize();

    bool quit = false;
    while (!quit) {

        ///// Updates

        g_time.Tick();

        g_audioSystem.Update();
        g_inputSystem.Update();

        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

        game->Update(g_time.GetDeltaTime());

        /////// Drawing

        g_renderer.SetColor(COLOR_SPLIT(game->GetBackgroundColor()));
        g_renderer.BeginFrame();

        game->Draw(g_renderer);

        g_renderer.EndFrame();

    }

    return 0;
}