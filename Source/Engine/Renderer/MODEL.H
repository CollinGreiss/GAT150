#pragma once

#include "Core/Math/Vector2.h"
#include "Core/Math/Transform.h"
#include "Core/Math/Color.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace kiko {

	class Renderer;

	class Model : public Resource {


	public:

		Model() = default;
		Model(std::vector<vec2> points) : m_points{ points } {}
		Model(const std::string& filename) { Load(filename); }

		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		virtual bool Create(std::string filename, ...) override;

		float GetRadius();

	private:

		std::vector<vec2> m_points;
		float m_radius = 0.0f;
		Color m_color;

	};

}