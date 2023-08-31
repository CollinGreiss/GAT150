#pragma once

#include "Component.h"

namespace kiko {

	class CollisionComponent : public Component {

	public:

		virtual bool CheckCollision(CollisionComponent* collision) { return true; };
		virtual float Top() { return -1.0; }
		virtual float Bottem() { return -1.0; }

	public:

		float radius = 0;

	};

}