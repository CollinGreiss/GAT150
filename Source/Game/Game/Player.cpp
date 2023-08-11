#include "Player.h"
#include "Projectile.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include <memory>
#include <iostream>

void Player::Update(float dt) {

    Actor::Update(dt);

    if (!GetComponent<kiko::PhysicsComponent>())
        return;

    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
    m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

    kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);


    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) GetComponent<kiko::PhysicsComponent>()->ApplyForce(forward * m_speed);

    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(
            kiko::Transform{ m_transform.position, m_transform.rotation, 1 },
            40.0f,
            m_tag,
            2.0f
            );

        std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
        component->m_texture = kiko::g_resources.Get<kiko::Texture>("images/rocket.png", kiko::g_renderer);
        projectile->AddComponent(std::move(component));

        std::unique_ptr<kiko::EnginePhysicsComponent> physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
        physicsComponent->m_damping = 0;
        physicsComponent->m_velocity = GetComponent<kiko::PhysicsComponent>()->m_velocity;
        physicsComponent->m_acceleration = (forward * m_speed * m_speed * m_speed);
       
        projectile->AddComponent(std::move(physicsComponent));

        m_scene->Add(std::move(projectile));

    }

    m_transform.position.x = kiko::Wrap(m_transform.position.x, kiko::g_renderer.GetWidth());
    m_transform.position.y = kiko::Wrap(m_transform.position.y, kiko::g_renderer.GetHeight());

}

void Player::OnCollision(Actor* other)
{
}
