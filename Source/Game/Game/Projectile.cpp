#include "Projectile.h"
#include "Input/InputSystem.h"
#include <Framework/Emitter.h>
#include "Framework/Scene.h"
#include <Framework/Components/PhysicsComponent.h>
#include "Renderer/Renderer.h"

void Projectile::Update(float dt) {

    Actor::Update(dt);

}

void Projectile::OnCollision(Actor* other) {

    if (other->GetTag() != m_tag) {

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
