#pragma once

#include "../../SimpleSfmlEngine/engine.hpp"
#include <SFML/Graphics.hpp>

namespace sse
{
	class SplashState : public State
	{
	public:
		explicit SplashState(GameDataRef data);

		bool Init() override;

		bool HandleInput(float dt) override;
		bool Update(float dt) override;
		bool Render(float dt) override;

	private:
		float m_pixel_threshold;

		GameDataRef m_data;
		sf::Clock m_clock;
		sf::Sprite m_background;
	};
}  // namespace sse