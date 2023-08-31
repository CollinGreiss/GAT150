#pragma once

#include "Framework/Actor.h"

namespace kiko {

	class Player : public Actor {

	public:

		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

		bool IsOnGround() { return groundCount.size() > 0; }

		friend class Player;

	private:

		float speed = 0;
		float jump = 0;
		std::vector<Actor*> groundCount;

		PhysicsComponent* m_physicsComponent = nullptr;
		AnimatedSpriteComponent* m_SpriteComponent = nullptr;

	};

}
