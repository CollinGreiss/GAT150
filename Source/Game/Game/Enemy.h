#pragma once
#include "Framework/Actor.h"

class Enemy : public kiko::Actor {

public:

	Enemy(float speed, const kiko::Transform& transform, float firerate, std::string tag) :
		Actor{ transform, tag, -1.0f },
		m_speed{ speed }
	{
		m_firerate = firerate;
		m_firetimer = m_firerate;
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:

	float m_speed = 0;

	float m_firerate = 0;
	float m_firetimer = 0;

};

