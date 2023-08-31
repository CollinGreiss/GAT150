#include "Player.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include <memory>
#include <iostream>

namespace kiko {

	CLASS_DEFINITION(Player);

	bool Player::Initialize() {

		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		if (!m_physicsComponent) ERROR_LOG("Physics component not found");

		m_SpriteComponent = GetComponent<AnimatedSpriteComponent>();
		if (!m_SpriteComponent) ERROR_LOG("Sprite component not found");

		return true;

	}

	void Player::Update(float dt) {

		Actor::Update(dt);
		
		vec2& velocity = m_physicsComponent->velocity;

		if (!m_physicsComponent || !m_SpriteComponent) return;

		if (speed != -1.0f) velocity.x = Clamp(velocity.x, -speed, speed);

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT) && !g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT)) {

			velocity.x -= speed * dt;
			m_SpriteComponent->flipH = true;
			m_SpriteComponent->SetSequence("walk");

		} else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_RIGHT) && !g_inputSystem.GetKeyDown(SDL_SCANCODE_LEFT)) {

			velocity.x += speed * dt;
			m_SpriteComponent->flipH = false;
			m_SpriteComponent->SetSequence("walk");

		} else {

			m_SpriteComponent->SetSequence("idle");

		}

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_UP) && IsOnGround()) {

			velocity.y = -jump;

		}

		if (transform.position.y >= g_renderer.GetHeight()) {

			EventManager::Instance().DispatchEvent("OnPlayerDead", NULL);
			m_destroyed = true;

		}

		if (velocity.y >= 1) m_SpriteComponent->SetSequence("fall");
		else if (velocity.y <= -1) m_SpriteComponent->SetSequence("jump");

		m_physicsComponent->SetVelocity(velocity);

	}

	void Player::OnCollisionEnter(Actor* other) {

		if (other->GetTag() == "Water")
			EventManager::Instance().DispatchEvent("OnPlayerDead", NULL);

		float distance = other->GetComponent<CollisionComponent>()->Top() - GetComponent<CollisionComponent>()->Bottem();
		if (distance < 5 && distance > -5)
			groundCount.push_back(other);

	}

	void Player::OnCollisionExit(Actor* other) {

		auto iter = std::find(groundCount.begin(), groundCount.end(), other);
		if (iter != groundCount.end())
			groundCount.erase(iter);

	}

	void Player::Read(const json_t& value) {

		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);

	}

}