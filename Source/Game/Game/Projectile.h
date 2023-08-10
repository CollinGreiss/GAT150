#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Projectile : public kiko::Actor {

public:

	Projectile(const kiko::Transform& transform, float damage, std::string tag, float lifespan = -1.0f) :
		Actor{ transform, tag, -1.0f, lifespan},
		m_damage{damage}
	{ };

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:

	float m_damage = 0;

};

