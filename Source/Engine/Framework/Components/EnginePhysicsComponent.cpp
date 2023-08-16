#include "EnginePhysicsComponent.h"

#include "Framework/Actor.h"

namespace kiko {

	CLASS_DEFINITION(EnginePhysicsComponent);

	void EnginePhysicsComponent::Update(float dt) {

		m_velocity += m_acceleration * dt;
		m_owner->GetTransform().position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);

	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force) {

		m_velocity += force;

	}

}