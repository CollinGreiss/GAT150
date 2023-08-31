#pragma once

#include "Scene.h"

#include <memory>


namespace kiko {

	class Game {

	public:

		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;

	protected:

		std::unique_ptr<Scene> m_scene;
		std::unique_ptr<Scene> m_gameLevel;

	};

}