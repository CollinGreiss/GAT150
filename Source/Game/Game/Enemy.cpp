#include "Enemy.h"

#include "Player.h"
#include "Framework/Emitter.h"
#include "Projectile.h"
#include "Framework/Scene.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Renderer.h"

#include <memory>

void Enemy::Update(float dt) {

    Actor::Update(dt);

    kiko::vec2 forward = kiko::vec2{ -1, 0 };
    transform.position += (forward * m_speed * dt);

    if (transform.position.x < -10.0f) {

        m_destroyed = true;

    }

    transform.position.y = kiko::Clamp(transform.position.y, 0.0f, (float)(kiko::g_renderer.GetHeight() - 28));

    m_firetimer -= dt;
    if (m_firetimer <= 0) {

        m_firetimer = m_firerate;
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(
            kiko::Transform{ transform.position, 0, 1 },
            40.0f,
            tag
            );
        m_scene->Add(std::move(projectile));

    }

}

void Enemy::OnCollision(Actor* other)
{
}
