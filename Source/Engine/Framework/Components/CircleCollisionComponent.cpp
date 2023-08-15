#include "CircleCollisionComponent.h"

#include "Framework/Actor.h"

void kiko::CircleCollisionComponent::Update(float dt) {


}

bool kiko::CircleCollisionComponent::CheckCollision(CollisionComponent* collision) {

    float distance = m_owner->GetTransform().position.Distance(collision->GetOwner()->GetTransform().position);
    float radius = m_radius + collision->m_radius;

    return (distance <= radius);

}
