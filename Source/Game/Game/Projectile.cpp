#include "Projectile.h"

#include "Input/InputSystem.h"
#include <Framework/Emitter.h>
#include "Framework/Scene.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Components/CollisionComponent.h"
#include "Renderer/Renderer.h"

namespace kiko {

    CLASS_DEFINITION(Projectile);

    bool Projectile::Initialize() {

        kiko::g_audioSystem.Play("laser");
        Actor::Initialize();

        m_physicsCompnent = GetComponent<PhysicsComponent>();

        vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);
        m_physicsCompnent->SetVelocity(forward * speed);

        auto collisoinComponent = GetComponent<CollisionComponent>();
        if (collisoinComponent) {

            auto renderComponent = GetComponent<RenderComponent>();
            if (renderComponent) {

                float sacle = transform.scale;
                collisoinComponent->radius = renderComponent->GetRadius();


            }

        }

        return true;

    }

    void Projectile::Update(float dt) {

        Actor::Update(dt);

    }

    void kiko::Projectile::Read(const json_t& value) {

        Actor::Read(value);
        READ_DATA(value, damage);
        READ_DATA(value, speed);

    }

    void Projectile::OnCollisionEnter(Actor* other) {

        if (other->GetTag() != GetTag()) {

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

            kiko::Transform transform{ transform.position, 0, 1 };
            auto emitter = std::make_unique<kiko::Emitter>(transform, data);
            emitter->SetLifespan(1.0f);
            m_scene->Add(std::move(emitter));

            kiko::g_audioSystem.Play("boom");

            SetLifespan(0.0f);
            other->Damage(damage);

        }

    }


}