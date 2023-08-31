#include "TilemapComponent.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Framework/Event/EventManager.h"

namespace kiko {

	CLASS_DEFINITION(TilemapComponent);

	bool TilemapComponent::Initialize() {

		select = m_owner->m_scene->GetActor("Select");

		for (int i = 0; i < tiles.size(); i++) {

			int index = tiles[i];
			if (index == 0) continue;

			auto actor = INSTANTIATE(Actor, tileNames[index]);

			if (actor) {
				int x = i % numColumns;
				int y = i / numColumns;

				actor->GetTransform().position = m_owner->GetTransform().position + (vec2{x, y} *size);
				actor->setPersistents(true);
				actor->m_scene = m_owner->m_scene;
				m_owner->m_scene->Add(std::move(actor));

			}

		}

		for (int i = tiles.size(); i < numRows * numColumns; i++)
			tiles.push_back(0);

		return true;

	}

	void TilemapComponent::Update(float dt) {

		if (!select)
			return;

		if (g_inputSystem.GetMouseButtonDown(2) && !g_inputSystem.GetMousePreviousButtonDown(2)) {
		
			select->disabled = !select->disabled;
			EventManager::Instance().DispatchEvent("OnDebugMode", !select->disabled);

		}

		if (select->disabled)
			return;

		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_1) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_1)) currentTiles = 1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_2) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_2)) currentTiles = 2;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_3) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_3)) currentTiles = 3;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_4) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_4)) currentTiles = 4;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_5) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_5)) currentTiles = 5;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_6) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_6)) currentTiles = 6;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_7) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_7)) currentTiles = 7;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_8) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_8)) currentTiles = 8;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_9) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_9)) currentTiles = 9;

		if (currentTiles >= tileNames.size()) currentTiles = tileNames.size() - 1;

		select->GetComponent<AnimatedSpriteComponent>()->SetSequence(currentTiles - 1);
		
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_LCTRL) &&(g_inputSystem.GetKeyDown(SDL_SCANCODE_S) && !g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_S))) {

			std::string filename = m_owner->m_scene->GetLevel();
			rapidjson::Document value;

			if (!Json::Load(filename, value)) {

				ERROR_LOG("Could not load scene file! " << filename);

			} else if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {

				for (auto& actorValue : GET_DATA(value, actors).GetArray()) {

					std::string name;
					READ_DATA(actorValue, name);

					if (name == m_owner->name)
						if (HAS_DATA(actorValue, components) && GET_DATA(actorValue, components).IsArray())
							for (auto& componentValue : GET_DATA(actorValue, components).GetArray())
								if (HAS_DATA(componentValue, tiles))
									WRITE_DATA(value, componentValue, tiles, filename);

				}

			}

		}

		int x = (int)(g_inputSystem.GetMousePosition().x / 48);
		int y = (int)(g_inputSystem.GetMousePosition().y / 48);

		select->GetTransform().position = (vec2{ x, y } * 48) + 24;


		if (g_inputSystem.GetMouseButtonDown(0) && (!g_inputSystem.GetMousePreviousButtonDown(0) || g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT)) && x < numColumns && y <= (numRows - 1)) {

			auto occupy = m_owner->m_scene->GetTile(select->GetTransform().position);

			if (!occupy || occupy->name != tileNames[currentTiles]) {

				if (occupy) occupy->Remove();

				auto actor = INSTANTIATE(Actor, tileNames[currentTiles]);

				if (actor) {

					tiles[x + y * numColumns] = currentTiles;
					actor->GetTransform().position = m_owner->GetTransform().position + (vec2{ x, y } *size);
					actor->setPersistents(true);
					actor->m_scene = m_owner->m_scene;
					actor->Initialize();
					m_owner->m_scene->Add(std::move(actor));

				}

			}

			EventManager::Instance().DispatchEvent("OnDebugMode", !select->disabled);

		}

		if (g_inputSystem.GetMouseButtonDown(1) && !g_inputSystem.GetMousePreviousButtonDown(1) && x < numColumns && y <= (numRows - 1) ) {

			auto actor = m_owner->m_scene->GetTile(select->GetTransform().position);

			if (actor) {

				tiles[x + y * numColumns] = 0;
				actor->Remove();

			}

		}

	}

	void TilemapComponent::Read(const json_t& value) {

		READ_DATA(value, numColumns);
		READ_DATA(value, numRows);
		READ_DATA(value, size);

		READ_DATA(value, tileNames);
		READ_DATA(value, tiles);

	}

}