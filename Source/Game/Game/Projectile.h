#pragma once

#include "Audio/AudioSystem.h"
#include "Core/Transform.h"
#include "Framework/Actor.h"

namespace kiko {

	class Projectile : public Actor {

	public:

		CLASS_DECLARATION(Projectile)

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* actor);

	private:

		float damage = 0;

	};


}
