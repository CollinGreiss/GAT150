#pragma once

#include "Component.h"
#include "Core/Vector2.h"

namespace kiko {

	class PhysicsComponent : public Component {

	public:

		virtual void Update(float dt) = 0;
		virtual void ApplyForce(const vec2& force) = 0;

	public:

		vec2 velocity;
		vec2 acceleration;
		float mass = 1.0f;
		float damping = 0;

	};

}