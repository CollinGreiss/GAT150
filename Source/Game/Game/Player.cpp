#include "Player.h"
#include "Projectile.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include <memory>

void Player::Update(float dt) {

    Actor::Update(dt);

    kiko::vec2 up = kiko::vec2{ 0, -1 };
    kiko::vec2 down = kiko::vec2{ 0, 1 };
    kiko::vec2 right = kiko::vec2{ 1, 0 };
    kiko::vec2 left = kiko::vec2{ -1, 0 };

    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W) && m_transform.position.y >= (kiko::g_renderer.GetHeight() - 28)) m_velocity.y = -300;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) m_velocity.x = m_speed;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) m_velocity.x = -m_speed;
    if (!kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && !kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) m_velocity.x = 0;

    AddForce(down * 3.0f);
    m_transform.position.x = kiko::Clamp(m_transform.position.x, 0.0f, (float) (kiko::g_renderer.GetWidth()));
    m_transform.position.y = kiko::Clamp(m_transform.position.y, 0.0f, (float) (kiko::g_renderer.GetHeight() - 28));


}

void Player::OnCollision(Actor* other)
{
}
