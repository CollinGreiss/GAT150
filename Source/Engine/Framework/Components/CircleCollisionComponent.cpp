#include "CircleCollisionComponent.h"

#include "Framework/Actor.h"

namespace kiko {

    CLASS_DEFINITION(CircleCollisionComponent);

    void CircleCollisionComponent::Update(float dt) {


    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision) {

        float distance = m_owner->GetTransform().position.Distance(collision->GetOwner()->GetTransform().position);
        float radius = m_radius + collision->m_radius;

        return (distance <= radius);

    }

}
