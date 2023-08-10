#pragma once

#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/SpriteComponent.h"
#include <memory>

namespace kiko {

	class Actor {

	public:

		Actor() = default;
		Actor(const kiko::Transform& transform, std::string tag, float health, float lifespan = -1.0f) :
			m_transform{ transform },
			m_tag{ tag },
			m_lifespan{ lifespan },
			m_health{ health }
		{}

		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		template<typename T>
		T* GetComponent();
		void AddComponent(std::unique_ptr<Component> component);

		virtual void OnCollision(Actor* other) {};

		float GetRadius() { return 30; }
		float GetHealth() { return m_health; }

		std::string GetTag() { return m_tag; }
		Transform& GetTransform() { return m_transform; }

		void SetLifespan(float lifespan) { m_lifespan = lifespan; }

		virtual void Damage(float damage) { if (m_health != -1.0f) m_health -= damage; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

	protected:

		bool m_destroyed = false;
		float m_lifespan = -1.0f;
		float m_health = -1.0f;

		Transform m_transform;
		std::string m_tag;

		std::vector<std::unique_ptr<Component>> m_components;

	};

	template<typename T>
	inline T* Actor::GetComponent() {

		for (auto& Component : m_components) {

			T* result = dynamic_cast<T*> (Component.get());
			if (result) return result;

		}

		return nullptr;

	}

}