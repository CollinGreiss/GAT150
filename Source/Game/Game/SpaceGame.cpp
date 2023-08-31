#include "SpaceGame.h"

#include "Player.h"
#include "Enemy.h"

#include "Core/Random.h"
#include "Core/Math/Color.h"
#include "Core/Math/Transform.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

using namespace kiko;

bool SpaceGame::Initialize() {

	m_scoreText = std::make_unique<Text>(GET_RESOURCE(Font, "fonts/ARCADECLASSIC.ttf", 24));
	m_scoreText->Create(kiko::g_renderer, "", kiko::Color{ 1, 1, 1, 1 });

	m_healthText = std::make_unique<Text>(GET_RESOURCE(Font, "fonts/ARCADECLASSIC.ttf", 24));
	m_healthText->Create(kiko::g_renderer, "", kiko::Color{ 1, 1, 1, 1 });

	g_audioSystem.AddAudio("laser", "sounds/laser.wav");
	g_audioSystem.AddAudio("boom", "sounds/explosion.wav");

	m_scene = std::make_unique<Scene>();
	m_scene->Load("json/scene.json");
	m_scene->Initialize();

	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;

}



void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt) {

	switch (m_state) {

	case SpaceGame::Title:

		
		if (auto text = m_scene->GetActor("GameOverText")) text->disabled = true;
		if (auto text = m_scene->GetActor("Background")) text->disabled = true;

		if (auto text = m_scene->GetActor("Title")) text->disabled = false;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			m_state = eState::StateGame;

		break;

	case SpaceGame::StateGame:

		if (auto text = m_scene->GetActor("Title")) text->disabled = true;
		m_score = 0;
		m_state = eState::StartLevel;

		break;

	case SpaceGame::StartLevel:
	{

		if (auto text = m_scene->GetActor("Background")) text->disabled = false;

		auto player = INSTANTIATE(Player, "Player");
		player->Initialize();
		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}

		break;

	case SpaceGame::Game:

		m_healthText->Create(g_renderer, "Health     " + std::to_string((int) m_scene->GetActor<Player>()->GetHealth()), { 1, 1, 1, 1 });

		m_spawnTimer += dt;

		if (m_spawnTimer >= m_spawnTime) {

			m_spawnTimer = randomf(0, m_spawnTime / 2);

			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->Initialize();
			m_scene->Add(std::move(enemy));

		}

		break;

	case SpaceGame::PlayerDead:

		m_scene->RemoveAll();
		
		m_state = eState::GameOver;
		break;

	case SpaceGame::GameOver:

		if (auto text = m_scene->GetActor("GameOverText")) text->disabled = false;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			m_state = eState::Title;

		break;

	default:
		break;

	}

	m_scoreText->Create(g_renderer, "Score     " + std::to_string(m_score), { 1, 1, 1, 1 });

	m_scene->Update(dt);

}

void SpaceGame::Draw(kiko::Renderer& renderer) {

	m_scene->Draw(renderer);


	m_scoreText->Draw(g_renderer, 10, 10);
	m_healthText->Draw(g_renderer, 200, 10);

}

void SpaceGame::OnAddPoints(const kiko::Event& event) {

	m_score += std::get<int>(event.data);

}

void SpaceGame::OnPlayerDead(const kiko::Event& event) {

	m_state = eState::PlayerDead;

}
