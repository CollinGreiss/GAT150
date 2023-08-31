#pragma once

#include "Framework/Actor.h"

namespace kiko {

	class Enemy : public kiko::Actor {

	public:
		
		CLASS_DECLARATION(Enemy)

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:

		float speed = 0;
		float turnRate = 0;

		float m_firerate = 0;
		float m_firetimer = 0;

	};

}