#pragma once

#include "Framework/Actor.h"
#include "Framework/Event/EventManager.h"

namespace kiko {

	class Platform : public Actor, IEventListener {

	public:

		CLASS_DECLARATION(Platform)

		bool Initialize() override;
		void Update(float dt) override;
		
		virtual void Remove() { m_destroyed = true; EVENT_UNSUBSCRIBE("OnSwitchDimension"); EVENT_UNSUBSCRIBE("OnDebugMode"); }
		
		void SwitchDimension(const Event& event);
		void OnDebugMode(const Event& event);

	private:

		int id = 0;
		int currentDimension = 1;
		bool debug = false;

		class Box2DPhysicsComponent* m_physicsComponent = nullptr;
		SpriteComponent* m_SpriteComponent = nullptr;
	
	};

}
