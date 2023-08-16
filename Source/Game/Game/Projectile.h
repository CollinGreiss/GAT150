#pragma once

#include "Framework/Components/Component.h"
#include "Audio/AudioSystem.h"

namespace kiko {

	class Projectile : public Component {

	public:

		/*Projectile(const kiko::Transform& transform, float damage, std::string tag, float lifespan = -1.0f) :
			Actor{ transform, tag, -1.0f, lifespan },
			m_damage{ damage }
		{};*/

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* actor);
		void Read(const json_t& value);

	private:

		float damage = 0;

	};


}
