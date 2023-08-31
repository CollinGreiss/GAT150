#include "Handler.h"

#include "Framework/Scene.h"
#include "Input/InputSystem.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include <memory>
#include <iostream>

namespace kiko {

	CLASS_DEFINITION(Handler);

	bool Handler::Initialize() {

		Actor::Initialize();

		dimensions.push_back(1);
		colors.push_back(std::string("66,  135, 245, 255"));
		colors.push_back(std::string("156, 11,  11,  255"));
		colors.push_back(std::string("201, 180, 14,  255"));
		colors.push_back(std::string("21,  163, 31,  255"));
		colors.push_back(std::string("128, 14,  130, 255"));

		return true;

	}

	void Handler::Update(float dt) {

		Actor::Update(dt);

		bool dispatch = false;
		
			 if (g_inputSystem.GetKeyDown(SDL_SCANCODE_1)) { if (dimensions.back() != 1 && dimensions.back() != 5) { timePast = -1.0f; dimensions.push_back(1); dispatch = true; }}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_2)) { if (dimensions.back() != 2 && dimensions.back() != 5) { timePast = -1.0f; dimensions.push_back(2); dispatch = true; }}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_3)) { if (dimensions.back() != 3 && dimensions.back() != 5) { timePast = -1.0f; dimensions.push_back(3); dispatch = true; }}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_4)) { if (dimensions.back() != 4 && dimensions.back() != 5) { timePast = timer; dimensions.push_back(4); dispatch = true; }}
		else if (g_inputSystem.GetKeyDown(SDL_SCANCODE_5)) { if (dimensions.back() != 5)						   { timePast = timer; dimensions.push_back(5); dispatch = true; }}

		if (dispatch) {
		
			EventManager::Instance().DispatchEvent("SetBackgroundColor", colors[dimensions.back() - 1]);
			EventManager::Instance().DispatchEvent("OnSwitchDimension", dimensions.back());
		
		}

		if (dimensions.size() > 3) dimensions.erase(dimensions.begin());
		
		if (timePast != -1.0) {

			timePast -= dt;

			if (timePast < 0) {

				timePast = -1.0f;

				EventManager::Instance().DispatchEvent("SetBackgroundColor", colors[dimensions[dimensions.size() - 2] - 1]);
				EventManager::Instance().DispatchEvent("OnSwitchDimension", dimensions[dimensions.size() - 2]);

				if (dimensions[dimensions.size() - 2] == 4 || dimensions[dimensions.size() - 2] == 5)
					timePast = timer;

				dimensions.pop_back();

			}

		}

	}

	void Handler::Read(const json_t& value) {

		Actor::Read(value);

	}

}