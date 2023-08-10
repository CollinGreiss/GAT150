#include "SpaceGame.h"

#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"


using namespace kiko;

bool SpaceGame::Initialize() {

	m_scoreText = std::make_unique<Text>(g_resources.Get<Font>("fonts/ARCADECLASSIC.ttf", 24));
	m_scoreText->Create(kiko::g_renderer, "", kiko::Color{ 1, 1, 1, 1 });

	m_healthText = std::make_unique<Text>(g_resources.Get<Font>("fonts/ARCADECLASSIC.ttf", 24));
	m_healthText->Create(kiko::g_renderer, "", kiko::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<Text>(g_resources.Get<Font>("fonts/ARCADECLASSIC.ttf", 600));

	g_audioSystem.AddAudio("laser", "sounds/laser.wav");
	g_audioSystem.AddAudio("boom", "sounds/explosion.wav");

	m_scene = std::make_unique<Scene>();

	return true;

}



void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt) {

	switch (m_state) {

	case SpaceGame::Title:

		m_titleText->Create(kiko::g_renderer, "Space Run", kiko::Color{ 1, 1, 1, 1 });
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			m_state = eState::StateGame;

		break;

	case SpaceGame::StateGame:

		m_score = 0;
		m_state = eState::StartLevel;

		break;

	case SpaceGame::StartLevel:
	{

		std::unique_ptr<Player> player = std::make_unique<Player>(
			100.0f, //health
			10.0f, //speed
			DegToRad(270.0f), //turn rate
			Transform{ {500, 300}, 0, 3 },
			"Player" //tag
			);

		std::unique_ptr<SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
		component->m_texture = g_resources.Get<Texture>("images/Main Ship/Main Ship - Bases/Main Ship - Base - Full health.png", g_renderer);
		player->AddComponent(std::move(component));

		std::unique_ptr<EnginePhysicsComponent> physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
		physicsComponent->m_damping = .9;
		player->AddComponent(std::move(physicsComponent));

		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}

		break;

	case SpaceGame::Game:

		if (!m_scene->GetActor<Player>()) {

			m_state = eState::PlayerDead;

		}
		else {

			m_healthText->Create(g_renderer, "Health     " + std::to_string((int) m_scene->GetActor<Player>()->GetHealth()), { 1, 1, 1, 1 });

		}

		m_spawnTimer += dt;

		if (m_spawnTimer >= m_spawnTime) {

			m_spawnTimer = randomf(0, m_spawnTime / 2);

			//Spawn some bullshit

		}

		break;

	case SpaceGame::PlayerDead:

		m_scene->RemoveAll();
		
		m_state = eState::GameOver;
		break;

	case SpaceGame::GameOver:

		m_titleText->Create(kiko::g_renderer, "Game Over!", kiko::Color{ 1, 1, 1, 1 });
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			m_state = eState::Title;

		break;

	default:
		break;

	}

	m_scoreText->Create(g_renderer, "Score     " + std::to_string(m_score), { 1, 1, 1, 1 });

	m_scene->Update(dt);
	g_particleSystem.Update(dt);

}

void SpaceGame::Draw(kiko::Renderer& renderer) {

	if (m_state == eState::Title || m_state == eState::GameOver)
		m_titleText->Draw(g_renderer, 300, 300);

	m_scoreText->Draw(g_renderer, 10, 10);
	m_healthText->Draw(g_renderer, 200, 10);

	m_scene->Draw(renderer);
	g_particleSystem.Draw(renderer);

}
