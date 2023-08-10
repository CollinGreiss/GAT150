#pragma once

#include "PhysicsComponent.h"
#include "Core/Vector2.h"

namespace kiko {

	class EnginePhysicsComponent : public PhysicsComponent {

	public:

		virtual void ApplyForce(const vec2& force) override;
		virtual void Update(float dt) override;

	public:
		

	};

}