#include "Box2DCollisionComponent.h"

#include "Box2DCollisionComponent.h"
#include "Box2DPhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko {

	CLASS_DEFINITION(Box2DCollisionComponent);

	bool Box2DCollisionComponent::Initialize() {

		auto component = m_owner->GetComponent<Box2DPhysicsComponent>();

		if (component) {

			data.size = data.size * scaleOffset * m_owner->GetTransform().scale;

			if (component->m_body->GetType() == b2_staticBody)
				PhysicsSystem::Instance().SetCollisionBoxStatic(component->m_body, data, m_owner);
			else
				PhysicsSystem::Instance().SetCollisionBox(component->m_body, data, m_owner);

		}

		return true;

	}

	void Box2DCollisionComponent::Update(float dt) {

	}

	float Box2DCollisionComponent::Top() {

		return m_owner->GetTransform().position.y - (data.size.y / 2);

	}

	float Box2DCollisionComponent::Bottem() {

		return m_owner->GetTransform().position.y + (data.size.y / 2);

	}

	void Box2DCollisionComponent::Read(const json_t& value) {

		READ_NAME_DATA(value, "size", data.size);
		READ_NAME_DATA(value, "density", data.density);
		READ_NAME_DATA(value, "friction", data.friction);
		READ_NAME_DATA(value, "resitution", data.restitution);
		READ_NAME_DATA(value, "isTrigger", data.isTrigger);

		READ_DATA(value, scaleOffset);

	}

}