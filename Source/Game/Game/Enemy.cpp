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
    m_transform.position += (forward * m_speed * dt);

    if (m_transform.position.x < -10.0f) {

        m_destroyed = true;

    }

    m_transform.position.y = kiko::Clamp(m_transform.position.y, 0.0f, (float)(kiko::g_renderer.GetHeight() - 28));

    m_firetimer -= dt;
    if (m_firetimer <= 0) {

        m_firetimer = m_firerate;
        std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(
            kiko::Transform{ m_transform.position, 0, 1 },
            40.0f,
            m_tag
            );
        m_scene->Add(std::move(projectile));

    }

}

void Enemy::OnCollision(Actor* other)
{
}
