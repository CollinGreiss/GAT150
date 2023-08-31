#pragma once

#include "SpriteComponent.h"
#include "Renderer/Texture.h"

namespace kiko {

	class AnimatedSpriteComponent : public SpriteComponent {

	public:

		CLASS_DECLARATION(AnimatedSpriteComponent)

		struct AnimSequence {

			std::string name;

			float fps = 0;
			int numColumns = 1;
			int numRows = 1;

			int startFrame = 1;
			int endFrame = 1;

			bool loop = true;

			std::shared_ptr<Texture> texture;

		};

		bool Initialize() override;
		void Update(float dt) override;

		void SetSequence(const std::string& name, bool update = true);
		void SetSequence(const int index, bool update = true) { SetSequence(m_names[index], update);}
		void UpdateSource();

	public:

		int frame = 0;
		float frameTimer = 0;

	private:

		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		std::vector<std::string> m_names;
		AnimSequence* m_sequence = nullptr;


	};

}

