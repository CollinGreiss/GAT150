#include "Player.h"
#include "Projectile.h"

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

        m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

        return true;

    }

    void Player::Update(float dt) {

        if (health <= 0.0f)
            kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 100);

        Actor::Update(dt);


        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) && m_physicsComponent) m_physicsComponent->ApplyTorque(-turnRate * dt);
        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && m_physicsComponent) m_physicsComponent->ApplyTorque(turnRate * dt);

        kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);


        if (m_physicsComponent && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) m_physicsComponent->ApplyForce(forward * speed);

        if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

            auto projectile = INSTANTIATE(kiko::Projectile, "Rocket");
            projectile->SetTransform({ transform.position + forward * 10, transform.rotation, 1 });
            projectile->SetTag(tag);
            projectile->Initialize();
            m_scene->Add(std::move(projectile));

        }

        transform.position.x = kiko::Wrap(transform.position.x, kiko::g_renderer.GetWidth());
        transform.position.y = kiko::Wrap(transform.position.y, kiko::g_renderer.GetHeight());

    }

    void Player::OnCollisionEnter(Actor* other) {
    }

    void Player::Read(const json_t& value) {

        Actor::Read(value);
        READ_DATA(value, speed);
        READ_DATA(value, turnRate);

    }

}
