#include "EnginePhysicsComponent.h"

#include "Framework/Actor.h"

namespace kiko {

	CLASS_DEFINITION(EnginePhysicsComponent);

	void EnginePhysicsComponent::Update(float dt) {

		velocity += acceleration * dt;
		m_owner->GetTransform().position += velocity * dt;
		velocity *= std::pow(1.0f - damping, dt);

	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force) {

		velocity += force;

	}

	void EnginePhysicsComponent::Read(const json_t& value) {
		
		READ_DATA(value, damping);
		READ_DATA(value, acceleration);
		READ_DATA(value, velocity);
		READ_DATA(value, mass);
	
	}

}