#pragma once

#include "Framework/Actor.h"
#include "Framework/Game.h"

class Obstacle : public kiko::Actor {

	public:

		Obstacle(float speed, const kiko::Transform& transform, std::shared_ptr<kiko::Model> model, std::string tag, kiko::Game* game) :
			Actor{ transform, model, tag, -1.0f, 0.0f },
			m_speed{ speed }
		{ m_game = game; }

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	private:

		float m_speed = 0;
		bool m_hit = false;


};

