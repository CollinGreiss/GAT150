#pragma once

#include "Framework/Actor.h"
#include "Framework/Event/EventManager.h"

namespace kiko {

	class Portal : public Actor, IEventListener {

	public:

		CLASS_DECLARATION(Portal)

		void OnCollisionEnter(Actor* other) override {

			if (other->GetTag() == "Player")
				EventManager::Instance().DispatchEvent("OnLevelSwitch", NULL);

		};

	};

}
