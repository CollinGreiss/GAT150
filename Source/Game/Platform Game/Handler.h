#pragma once

#include "Framework/Actor.h"

namespace kiko {

	class Handler : public Actor {

	public:

		CLASS_DECLARATION(Handler)

		bool Initialize() override;
		void Update(float dt) override;

	private:

		float timer = 3.0f;
		float timePast = -1.0;
		std::vector<int> dimensions;
		std::vector<std::string> colors;

	};

}
