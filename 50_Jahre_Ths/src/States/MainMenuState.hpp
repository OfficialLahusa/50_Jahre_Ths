#pragma once
#include "../../SimpleSfmlEngine/engine.hpp"
#include "../GLOBAL_DEFINITIONS.hpp"
#include <iostream>
#include "../../ReadandWrite.hpp"

namespace sse
{
	class MainMenuState : public State
	{
	public:
		explicit MainMenuState(GameDataRef data);

		bool Init() override;

		bool HandleInput(float dt) override;
		bool Update(float dt) override;
		bool Render(float dt) override;

	private:
		bool IsFocussedSoundPlayed = false;
		bool IsKlickSoundPlayed = false;
		bool EingabeLäuft = false;

		std::string name;

		sf::Sprite m_background;

		GameDataRef m_data;

		sf::Clock m_Clock;

		sf::Sprite m_Button;

		sf::Sound m_FocussedSound;
		sf::Sound m_KlickSound;

		sf::Text m_ButtonText;
		sf::Text m_Aufforderung;
		sf::Text m_name;

		ReadandWrite *rw;
	};
}