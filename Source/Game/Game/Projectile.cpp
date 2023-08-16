#include "Projectile.h"
#include "Input/InputSystem.h"
#include <Framework/Emitter.h>
#include "Framework/Scene.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Components/CollisionComponent.h"
#include "Renderer/Renderer.h"

namespace kiko {

    bool Projectile::Initialize() {

        kiko::g_audioSystem.Play("laser");
        auto collisoinComponent = m_owner->GetComponent<kiko::CollisionComponent>();

        return true;

    }

    void Projectile::Update(float dt) {

        Actor::Update(dt);

    }

    void kiko::Projectile::Read(const json_t& value {

        READ_DATA(value, damage)

    }

    void Projectile::OnCollision(Actor* other) {

        if (other->GetTag() != m_owner->GetTag()) {

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

            kiko::Transform transform{ transform.position, 0, 1 };
            auto emitter = std::make_unique<kiko::Emitter>(transform, data);
            emitter->SetLifespan(1.0f);
            m_scene->Add(std::move(emitter));

            kiko::g_audioSystem.Play("boom");

            m_owner->SetLifespan(0.0f) = true;
            other->Damage(damage);

        }

    }


}