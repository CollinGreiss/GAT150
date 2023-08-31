#pragma once
#include "Framework/Actor.h"

namespace kiko {

	class Player : public kiko::Actor {

	public:
		
		CLASS_DECLARATION(Player)

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

		friend class Player;

	private:

		float speed = 0;
		float turnRate = 0;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;

	};

}

