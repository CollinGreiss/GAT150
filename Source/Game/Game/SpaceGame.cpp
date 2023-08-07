#include "SpaceGame.h"

#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/SpriteComponent.h"

#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"

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

		auto player = std::make_unique<Player>(
			100.0f,
			150.0f,
			DegToRad(270.0f),
			Transform{ {50, (g_renderer.GetHeight() - 28)}, 0, 3 },
			g_modelManager.Get("models/ship.txt"),
			"Player",
			0.0f
			);

		std::unique_ptr<SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
		//component->m_texture = g_resources.Get<Texture>("images/Main Ship/Main Ship - Bases/Main Ship - Base - Full health.png");
		component->m_texture = g_resources.Get<Texture>("images/gary.png");
		player->AddComponent(std::move(component));


		m_scene->Add(std::move(player));

		m_state = eState::Game;

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

			switch (random(0, 3)) {

			case 0:

				m_scene->Add(std::make_unique <Obstacle>(
					50.0f + m_score,
					Transform{
						{(float)g_renderer.GetWidth(), (float)g_renderer.GetHeight() - 124 },
						0,
						2
					},
					g_modelManager.Get("models/bird.txt"),
					"Bird",
					this
					));

				break;

			case 1:

				m_scene->Add(std::make_unique <Obstacle>(
					50.0f + m_score,
					Transform{
						{(float)g_renderer.GetWidth(), (float)g_renderer.GetHeight() - 24 },
						0,
						2
					},
					g_modelManager.Get("models/cactus.txt"),
					"Cactus",
					this
					));

				break;
			case 2:

				m_scene->Add(std::make_unique <Enemy>(
					50.0f + m_score,
					Transform{
						{(float)g_renderer.GetWidth(), 100.0f},
						DegToRad(270),
						2
					},
					g_modelManager.Get("models/enemy.txt"),
					5.0f,
					"enemy"
					));

				break;

			default:
				break;
			}
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
