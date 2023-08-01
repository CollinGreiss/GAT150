#include "Obstacle.h"
#include "Framework/Emitter.h"

void Obstacle::Update(float dt) {

    Actor::Update(dt);

    kiko::vec2 forward = kiko::vec2{ -1, 0 };
    m_transform.position += (forward * m_speed * dt);

    if (m_transform.position.x < -10.0f) {

        m_game->AddPoints(5);
        m_destroyed = true;

    }

    m_transform.position.y = kiko::Clamp(m_transform.position.y, 0.0f, (float)(kiko::g_renderer.GetHeight() - 28));

}

void Obstacle::OnCollision(Actor* other) {

    if (other->GetTag() == "Player" && !m_hit) {
        other->Damage(40);
        m_hit = true;
    }
}
