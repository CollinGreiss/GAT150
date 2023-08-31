#include "CircleCollisionComponent.h"

#include "Framework/Actor.h"

namespace kiko {

    CLASS_DEFINITION(CircleCollisionComponent);

    void CircleCollisionComponent::Update(float dt) {


    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision) {

        float distance = m_owner->GetTransform().position.Distance(collision->GetOwner()->GetTransform().position);
        float radius = this->radius + collision->radius;

        return (distance <= radius);

    }

    void CircleCollisionComponent::Read(const json_t& value) {
    

    
    }

}
