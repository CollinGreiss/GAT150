#pragma once

#include "PhysicsComponent.h"
#include "Core/Math/Vector2.h"

namespace kiko {

	class EnginePhysicsComponent : public PhysicsComponent {

	public:

		CLASS_DECLARATION(EnginePhysicsComponent)

		virtual void Update(float dt);
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float Torque) override {};

	public:
		

	};

}