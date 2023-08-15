#include "Actor.h"

#include "Components/CircleCollisionComponent.h"

namespace kiko {

	bool Actor::Initialize() {

		for (auto& component : m_components)
			component->Initialize();

		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (collisionComponent && renderComponent)
			collisionComponent->m_radius = renderComponent->GetRadius() * m_transform.scale;

		return true;

	}

	void Actor::OnDestroy() {

		for (auto& component : m_components)
			component->OnDestroy();

	}

	void Actor::Update(float dt){

		if (m_lifespan != -1.0f)
			(m_lifespan > 0) ? m_lifespan -= dt : m_destroyed = true;

		if (m_health <= 0 && m_health != -1.0f)
			m_destroyed = true;

		if ((GetComponent<PhysicsComponent>()))
			GetComponent<PhysicsComponent>()->Update(dt);

	}

	void Actor::Draw(kiko::Renderer& renderer) {

		//m_model->Draw(renderer, GetTransform());
		for (auto& component : m_components) {

			if (dynamic_cast<RenderComponent*> (component.get()))
				dynamic_cast<RenderComponent*> (component.get())->Draw(renderer);

		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {

		component->m_owner = this;
		m_components.push_back(std::move(component));

	}


}