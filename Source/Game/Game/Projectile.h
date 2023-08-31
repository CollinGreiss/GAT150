#pragma once

#include "Audio/AudioSystem.h"
#include "Core/Math/Transform.h"
#include "Framework/Actor.h"

namespace kiko {

	class Projectile : public Actor {

	public:

		CLASS_DECLARATION(Projectile)

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* actor);

	private:

		float speed = 0;
		float damage = 0;
		PhysicsComponent* m_physicsCompnent = nullptr;

	};


}
