#pragma once

#include "Object.h"
#include "Core/Math/Transform.h"
#include "Core/Math/Vector2.h"
#include "Renderer/Model.h"
#include "Components/AnimatedSpriteComponent.h"
#include "Components/EnginePhysicsComponent.h"
#include <memory>

namespace kiko {

	class Actor : public Object {

	public:

		CLASS_DECLARATION(Actor)

		Actor() = default;

		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}

		Actor(const Actor& other);

		virtual ~Actor() {

			OnDestroy();

		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		template<typename T>
		T* GetComponent();
		void AddComponent(std::unique_ptr<Component> component);

		virtual void OnCollisionEnter(Actor* other) {};
		virtual void OnCollisionExit(Actor* other) {};

		float GetHealth() { return health; }
		bool isPersistent() { return persistent; }
		bool IsDestroyed() { return m_destroyed; }

		std::string GetTag() { return tag; }
		Transform& GetTransform() { return transform; }

		void SetTransform(const Transform& transform) { this->transform = transform; }
		void SetHealth(float health) { this->health = health; }
		void SetLifespan(float lifespan) { this->lifespan = lifespan; }
		void SetTag(std::string tag) { this->tag = tag; }
		void setPersistents(bool persistent) { this->persistent = persistent; }

		virtual void AddHealth(float health) { this->health += health; }
		virtual void Damage(float damage) { if (health != -1.0f) health -= damage; }
		virtual void Remove() { m_destroyed = true; }

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

	protected:

		bool m_destroyed = false;
		float lifespan = -1.0f;
		float health = -1.0f;
		bool persistent = false;
		bool prototype = false;

		Transform transform;
		std::string tag;

		std::vector<std::unique_ptr<Component>> components;

	};

	template<typename T>
	inline T* Actor::GetComponent() {

		for (auto& component : components) {

			T* result = dynamic_cast<T*> (component.get());
			if (result) return result;

		}

		return nullptr;

	}

}