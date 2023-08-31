#pragma once

#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Framework/Event/EventManager.h"
#include "Core/Math/Color.h"

class PlatformGame : public kiko::Game, kiko::IEventListener {

public:
	enum eState {

		Title,
		StateGame,
		StartLevel,
		Game,
		PlayerDead,
		NewLevel

	};

public:

	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	kiko::Color& GetBackgroundColor() { return m_backgroundColor; }

	void OnPlayerDead(const kiko::Event& event);
	void OnLevelSwitch(const kiko::Event& event);
	void OnDebugMode(const kiko::Event& event);
	void SetBackgroundColor(const kiko::Event& event);

private:

	kiko::Color m_backgroundColor{ 66, 135, 245, 255 };
	eState m_state = eState::Title;

	bool debug = false;

	std::vector<std::string> m_levels;
	int m_currentLevel = 0;

};