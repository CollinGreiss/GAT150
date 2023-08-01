#include "Projectile.h"
#include "Input/InputSystem.h"
#include <Framework/Emitter.h>
#include "Framework/Scene.h"

void Projectile::Update(float dt) {

    Actor::Update(dt);

    kiko::vec2 down = kiko::vec2{ 0, 1 };

    AddForce(down * 3.0f);

    m_time += dt;

    if (m_time >= 10.0f) {

        kiko::EmitterData data;

        data.burst = true;
        data.burstCount = 100;
        data.spawnRate = 200;
        data.angle = 0;
        data.angleRange = kiko::Pi;
        data.lifetimeMin = 0.5f;
        data.lifetimeMin = 1.5f;
        data.speedMin = 50;
        data.speedMax = 250;
        data.damping = 0.5f;
        data.color = kiko::Color{ 1.0f, 0.1f, 0.0f, 1.0f };

        kiko::Transform transform{ m_transform.position, 0, 1 };
        auto emitter = std::make_unique<kiko::Emitter>(transform, data);
        emitter->SetLifespan(1.0f);
        m_scene->Add(std::move(emitter));

        kiko::g_audioSystem.Play("boom");

        m_destroyed = true;

    }

    m_transform.position.y = kiko::Clamp(m_transform.position.y, 0.0f, (float)(kiko::g_renderer.GetHeight() - 28));

}

void Projectile::OnCollision(Actor* other) {

    if (other->GetTag() == "Player") {

        kiko::EmitterData data;

        data.burst = true;
        data.burstCount = 100;
        data.spawnRate = 200;
        data.angle = 0;
        data.angleRange = kiko::Pi;
        data.lifetimeMin = 0.5f;
        data.lifetimeMin = 1.5f;
        data.speedMin = 50;
        data.speedMax = 250;
        data.damping = 0.5f;
        data.color = kiko::Color{ 1, 0.1, 0, 1 };

        kiko::Transform transform{ m_transform.position, 0, 1 };
        auto emitter = std::make_unique<kiko::Emitter>(transform, data);
        emitter->SetLifespan(1.0f);
        m_scene->Add(std::move(emitter));

        kiko::g_audioSystem.Play("boom");

        m_destroyed = true;
        other->Damage(m_damage);

    }

}
