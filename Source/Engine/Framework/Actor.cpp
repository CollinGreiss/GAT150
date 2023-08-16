#include "Actor.h"

#include "Components/CircleCollisionComponent.h"

namespace kiko {

	CLASS_DEFINITION(Actor);

	bool Actor::Initialize() {

		for (auto& component : components)
			component->Initialize();

		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (collisionComponent && renderComponent)
			collisionComponent->m_radius = renderComponent->GetRadius() * transform.scale;

		return true;

	}

	void Actor::OnDestroy() {

		for (auto& component : components)
			component->OnDestroy();

	}

	void Actor::Update(float dt){

		if (lifespan != -1.0f)
			(lifespan > 0) ? lifespan -= dt : m_destroyed = true;

		if (health <= 0 && health != -1.0f)
			m_destroyed = true;

		if ((GetComponent<PhysicsComponent>()))
			GetComponent<PhysicsComponent>()->Update(dt);

	}

	void Actor::Draw(kiko::Renderer& renderer) {

		for (auto& component : components) {

			if (dynamic_cast<RenderComponent*> (component.get()))
				dynamic_cast<RenderComponent*> (component.get())->Draw(renderer);

		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {

		component->m_owner = this;
		components.push_back(std::move(component));

	}

	void Actor::Read(const rapidjson::Value& value) {

		Object::Read(value);
		
		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, health);

		if (HAS_DATA(value, transform)) transform.Read(value);

		if (HAS_DATA(value, #components) && GET_DATA(value, components).IsArray()) {

			for (auto& componentValue : GET_DATA(value, components).GetArray()) {

				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(kiko::Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component));

			}

		}

	}

}