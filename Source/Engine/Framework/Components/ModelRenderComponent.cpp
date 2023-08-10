#include "ModelRenderComponent.h"

#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace kiko {

	void ModelRenderComponent::Update(float dt) {


	}

	void ModelRenderComponent::Draw(Renderer& renderer) {

		m_model->Draw(renderer, m_owner->GetTransform());

	}

}