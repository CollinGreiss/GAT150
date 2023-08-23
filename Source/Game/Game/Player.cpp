#include "Player.h"
#include "Projectile.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include <memory>
#include <iostream>

bool Player::Initialize() {

    Actor::Initialize();

    m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

    return true;

}

void Player::Update(float dt) {

    if (health <= 0.0f)
        kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 100);

    Actor::Update(dt);

    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

    transform.rotation += rotate * m_turnRate * dt;

    kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);


    if (m_physicsComponent && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) m_physicsComponent->ApplyForce(forward * m_speed);

    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

        auto projectile = INSTANTIATE(kiko::Projectile, "Rocket");
        projectile->SetTransform( { transform.position, transform.rotation, 1 } );
        if (auto physicsComponent = projectile->GetComponent<kiko::PhysicsComponent>()) {

            if (m_physicsComponent) physicsComponent->velocity = m_physicsComponent->velocity;
            physicsComponent->acceleration = forward * m_speed * m_speed * m_speed;

        }
        projectile->Initialize();
        m_scene->Add(std::move(projectile));

    }

    transform.position.x = kiko::Wrap(transform.position.x, kiko::g_renderer.GetWidth());
    transform.position.y = kiko::Wrap(transform.position.y, kiko::g_renderer.GetHeight());

}

void Player::OnCollision(Actor* other)
{
}
