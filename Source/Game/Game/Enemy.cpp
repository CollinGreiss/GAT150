#include "Enemy.h"

#include "Player.h"
#include "Framework/Emitter.h"
#include "Projectile.h"
#include "Framework/Framework.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Renderer.h"

#include <memory>

namespace kiko {

    CLASS_DEFINITION(Enemy);

    void Enemy::Update(float dt) {

        if (health <= 0.0f)
            kiko::EventManager::Instance().DispatchEvent("OnAddPoints", 100);

        Actor::Update(dt);

        kiko::vec2 forward = kiko::vec2{ -1, 0 };
        transform.position += (forward * speed * dt);

        if (transform.position.x < -10.0f) {

            m_destroyed = true;

        }

        transform.position.y = kiko::Clamp(transform.position.y, 0.0f, (float)(kiko::g_renderer.GetHeight() - 28));

        m_firetimer -= dt;
        if (m_firetimer <= 0) {

            m_firetimer = m_firerate;

        }

    }

    void Enemy::OnCollisionEnter(Actor* other) {
    }

    void Enemy::Read(const json_t& value) {

        Actor::Read(value);
        READ_DATA(value, speed);
        READ_DATA(value, turnRate);

    }

}