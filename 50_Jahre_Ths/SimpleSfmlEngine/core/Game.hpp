#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>

#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "StateMachine.hpp"

namespace sse
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	using GameDataRef = std::shared_ptr<GameData>;

	class Game
	{
	public:
		Game(const std::string& title, const std::function<void(GameDataRef data)>& runState)
		{
			this->m_data->window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
			this->m_data->window.setVerticalSyncEnabled(true);

			runState(this->m_data);

			this->Run();
		}

	private:
		sf::Clock m_clock;

		GameDataRef m_data = std::make_shared<GameData>();

		void Run()
		{

			while (this->m_data->window.isOpen())
			{
				if (!this->m_data->machine.ProcessStateChanges()) { return; }
				float dt = m_clock.restart().asSeconds();
				
				// TODO(Bernstein): handle return type
				if (!this->m_data->machine.GetActiveState()->HandleInput(dt)) { return; }
				if (!this->m_data->machine.GetActiveState()->Update(dt)) { return; }

				if (!this->m_data->machine.GetActiveState()->Render(dt)) { return; }

			}
		}
	};
}  // namespace sse
