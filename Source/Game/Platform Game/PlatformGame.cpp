#include "PlatformGame.h"

#include "Player.h"

#include "Core/Random.h"
#include "Core/Math/Color.h"
#include "Core/Math/Transform.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

using namespace kiko;

bool PlatformGame::Initialize() {

	m_scene = std::make_unique<Scene>();

	m_scene->Load("json/platform.json");
	m_scene->Initialize();

	m_gameLevel = std::make_unique<Scene>();

	m_gameLevel->SetLevel("json/level1.json");
	m_gameLevel->Initialize();


	m_levels.push_back("json/level1.json");
	m_levels.push_back("json/level2.json");
	m_levels.push_back("json/level3.json");
	m_levels.push_back("json/level4.json");
	m_levels.push_back("json/level5.json");


	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);
	EVENT_SUBSCRIBE("OnDebugMode", PlatformGame::OnDebugMode);
	EVENT_SUBSCRIBE("OnLevelSwitch", PlatformGame::OnLevelSwitch);
	EVENT_SUBSCRIBE("SetBackgroundColor", PlatformGame::SetBackgroundColor);

	return true;

}



void PlatformGame::Shutdown() {

}

void PlatformGame::Update(float dt) {

	PhysicsSystem::Instance().Update(dt);

	switch (m_state) {

	case PlatformGame::Title:

		m_scene->SetDisabledAll(true);
		if (auto text = m_scene->GetActor("Title")) text->disabled = false;

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
			m_state = eState::StateGame;

		break;

	case PlatformGame::StateGame:

		m_scene->SetDisabledAll(false);
		if (auto text = m_scene->GetActor("Title")) text->disabled = true;

		m_state = eState::StartLevel;

		break;

	case PlatformGame::StartLevel:
	{

		auto player = INSTANTIATE(Player, "Player");
		player->Initialize();
		m_gameLevel->Add(std::move(player));

	}

	m_state = eState::Game;
	break;

	case PlatformGame::Game:

		break;

	case PlatformGame::PlayerDead:

	{
		auto player = m_gameLevel->GetActor<Player>();
		player->Remove();
		m_state = eState::StartLevel;
	}

	break;

	case PlatformGame::NewLevel:

		m_scene->RemoveAll();
		m_gameLevel->RemoveAll(true);

		m_gameLevel = std::make_unique<Scene>();

		m_currentLevel++;
		m_currentLevel %= m_levels.size();

		m_gameLevel->SetLevel(m_levels[m_currentLevel]);
		m_gameLevel->Initialize();

		m_state = eState::StartLevel;

		break;

	default:
		break;

	}

	m_scene->Update(dt);
	m_gameLevel->Update(dt);
	g_particleSystem.Update(dt);

}

void PlatformGame::Draw(kiko::Renderer& renderer) {

	m_scene->Draw(renderer);
	m_gameLevel->Draw(renderer);
	g_particleSystem.Draw(g_renderer);

}

void PlatformGame::OnPlayerDead(const kiko::Event& event) { 

	m_scene->RemoveAll();
	m_state = eState::PlayerDead;

}

void PlatformGame::OnLevelSwitch(const kiko::Event& event) {

	m_state = eState::NewLevel;

}

void PlatformGame::OnDebugMode(const kiko::Event& event) {
	
	debug = std::get<bool>(event.data);

	if (!debug) return;

	m_backgroundColor.r = 66;
	m_backgroundColor.g = 135;
	m_backgroundColor.b = 245;
	m_backgroundColor.a = 255;

}

void PlatformGame::SetBackgroundColor(const kiko::Event& event) {

	if (debug) return;

	std::string data = std::get<std::string>(event.data);

	std::istringstream iss(data);

	float r, g, b, a;

	char comma;
	iss >> r >> comma >> g >> comma >> b >> comma >> a;

	m_backgroundColor.r = r;
	m_backgroundColor.g = g;
	m_backgroundColor.b = b;
	m_backgroundColor.a = a;

}
