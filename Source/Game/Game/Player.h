#pragma once
#include "Framework/Actor.h"

class Player : public kiko::Actor {

public:

	Player(float health, float speed, float turnRate, const kiko::Transform& transform, std::string tag) :
		Actor{ transform, tag, health },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	
	float m_speed = 0;
	float m_turnRate = 0;

};

