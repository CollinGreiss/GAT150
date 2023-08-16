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

    Actor::Update(dt);

    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

    transform.rotation += rotate * m_turnRate * dt;

    kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);


    if (m_physicsComponent && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) m_physicsComponent->ApplyForce(forward * m_speed);

    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {

        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(
            kiko::Transform{ transform.position, transform.rotation, 1 },
            40.0f,
            tag,
            2.0f
            );

        std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
        component->m_texture = GET_RESOURCE(kiko::Texture, "images/rocket.png", kiko::g_renderer);
        projectile->AddComponent(std::move(component));

        std::unique_ptr<kiko::EnginePhysicsComponent> physicsComponent = std::make_unique<kiko::EnginePhysicsComponent>();
        physicsComponent->m_damping = 0;
        if (m_physicsComponent) physicsComponent->m_velocity = m_physicsComponent->m_velocity;
        physicsComponent->m_acceleration = (forward * m_speed * m_speed * m_speed);
       
        projectile->AddComponent(std::move(physicsComponent));

        auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
        projectile->AddComponent(std::move(collisionComponent));

        projectile->Initialize();

        m_scene->Add(std::move(projectile));

    }

    transform.position.x = kiko::Wrap(transform.position.x, kiko::g_renderer.GetWidth());
    transform.position.y = kiko::Wrap(transform.position.y, kiko::g_renderer.GetHeight());

}

void Player::OnCollision(Actor* other)
{
}
