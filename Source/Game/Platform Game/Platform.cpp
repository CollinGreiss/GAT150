#include "Platform.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Framework/Components/Box2DPhysicsComponent.h"

#include <memory>
#include <iostream>

namespace kiko {

	CLASS_DEFINITION(Platform);

	bool Platform::Initialize() {

		Actor::Initialize();

		m_physicsComponent = GetComponent<Box2DPhysicsComponent>();
		if (!m_physicsComponent) ERROR_LOG("Physics component not found");

		m_SpriteComponent = GetComponent<SpriteComponent>();
		if (!m_SpriteComponent) ERROR_LOG("Sprite component not found");

		EVENT_SUBSCRIBE("OnSwitchDimension", Platform::SwitchDimension);
		EVENT_SUBSCRIBE("OnDebugMode", Platform::OnDebugMode);

		if (m_SpriteComponent && m_physicsComponent) {

			m_SpriteComponent->disabled = (id != 1);
			m_physicsComponent->disabled = (id != 1);

			m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/box.png", g_renderer);

		}

		return true;

	}

	void Platform::Update(float dt) {

		Actor::Update(dt);

	}

	void Platform::SwitchDimension(const kiko::Event& event) {

		int swap = std::get<int>(event.data);

		if (debug)
			return;

		m_SpriteComponent->disabled = (id != swap);
		m_physicsComponent->disabled = (id != swap);

	}

	void Platform::OnDebugMode(const kiko::Event& event) {

		debug = std::get<bool>(event.data);

		if (debug) {

			m_SpriteComponent->disabled = false;
			m_physicsComponent->disabled = false;

			if (id == 1) m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/blue.png", g_renderer);
			else if (id == 2) m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/red.png", g_renderer);
			else if (id == 3) m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/yellow.png", g_renderer);
			else if (id == 4) m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/green.png", g_renderer);
			else if (id == 5) m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/purple.png", g_renderer);

		} else {

			m_SpriteComponent->m_texture = GET_RESOURCE(Texture, "images/box.png", g_renderer);
			m_SpriteComponent->disabled = (id != 1);
			m_physicsComponent->disabled = (id != 1);

		}

	}

	void Platform::Read(const json_t& value) {

		Actor::Read(value);

		READ_DATA(value, id);

	}

}