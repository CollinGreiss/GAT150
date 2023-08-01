#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Projectile : public kiko::Actor {

public:

	Projectile(const kiko::Transform& transform, std::shared_ptr<kiko::Model> model, float damage) :
		Actor{ transform, model, "Bomb", -1.0f, 0.0f},
		m_damage{damage}
	{ };

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:

	float m_time;
	float m_damage = 0;
};

