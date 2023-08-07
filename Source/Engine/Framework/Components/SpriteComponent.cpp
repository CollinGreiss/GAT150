#include "SpriteComponent.h"

#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace kiko {

	void SpriteComponent::Update(float dt) {


	}

	void SpriteComponent::Draw(Renderer& renderer) {

		renderer.DrawTexture(m_texture.get(), m_owner->GetTransform().position.x, m_owner->GetTransform().position.y, m_owner->GetTransform().rotation);

	}

}