#include "MainMenuState.hpp"

namespace sse
{
	MainMenuState::MainMenuState(GameDataRef data) : m_data(data)
	{
		rw = new ReadandWrite();

		//loadings
		m_data->assets.LoadTexture("Buttons", BUTTONS);

		m_data->assets.LoadSoundBuffer("focussed", FOCUSSED_SOUND);
		m_data->assets.LoadSoundBuffer("klick", KLICK_SOUND);

		m_data->assets.LoadFont("font", FONT);

		//Buttons
		m_Button.setTexture(m_data->assets.GetTexture("Buttons"));
		m_Button.setScale({ 4,4 });
		m_Button.setTextureRect(sf::IntRect(0, 0, 64, 32));
		m_Button.setPosition({ m_data->window.getSize().x / 2 - m_Button.getGlobalBounds().width / 2, m_data->window.getSize().y / 2 - m_Button.getGlobalBounds().height / 2});	

		//Sound
		m_FocussedSound.setBuffer(m_data->assets.GetSoundBuffer("focussed"));
		m_FocussedSound.setVolume(10);
		m_KlickSound.setBuffer(m_data->assets.GetSoundBuffer("klick"));

		//Text im Button
		m_ButtonText.setFont(m_data->assets.GetFont("font"));
		m_ButtonText.setString("Start");
		m_ButtonText.setCharacterSize(35);
		m_ButtonText.setPosition(m_Button.getPosition().x + m_Button.getGlobalBounds().width / 2 - m_ButtonText.getGlobalBounds().width / 2, m_Button.getPosition().y + m_Button.getGlobalBounds().height / 2 - m_ButtonText.getGlobalBounds().height / 1.5f);

		//Text oben
		m_Aufforderung.setFont(m_data->assets.GetFont("font"));
		m_Aufforderung.setString("\t\t\t\t\t\t\t\t\tBitte gebe deinen Namen ein!\nUm die Eingabe zu starten druecke auf den Start-Knopf!");
		m_Aufforderung.setCharacterSize(40);
		m_Aufforderung.setPosition(m_data->window.getSize().x / 2 - m_Aufforderung.getGlobalBounds().width / 2, m_data->window.getSize().y / 2 - m_Aufforderung.getGlobalBounds().height * 5);

		//Name
		m_name.setFont(m_data->assets.GetFont("font"));
		m_name.setString("Dein Name lautet: " + rw->Read("Resources/data/name.txt"));
		m_name.setCharacterSize(30);
		m_name.setPosition(m_data->window.getSize().x / 2 - m_name.getGlobalBounds().width / 2, m_data->window.getSize().y / 2 - m_name.getGlobalBounds().height * 5);
	}

	bool MainMenuState::Init()
	{
		return true;
	}

	bool MainMenuState::HandleInput(float dt)
	{
		sf::Event evnt;

		while (m_data->window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
			if (evnt.type == sf::Event::Resized) {
				m_data->window.setSize(sf::Vector2u(evnt.size.width, evnt.size.height));
			}
			if (EingabeLäuft)
			{
				if (evnt.type == sf::Event::TextEntered)
				{
					if (evnt.text.unicode < 128)
					{
						if (evnt.text.unicode == 8)
						{
							name = "";
							m_name.setString("Dein Name lautet: " + name);
							m_name.setPosition(m_data->window.getSize().x / 2 - m_name.getGlobalBounds().width / 2, m_data->window.getSize().y / 2 - m_name.getGlobalBounds().height * 5);
						}						
						else
						{							
							if (m_name.getGlobalBounds().width >= m_data->window.getSize().x - 30)
							{
								name = name;
								m_name.setString("Dein Name lautet: " + name);
								m_name.setPosition(m_data->window.getSize().x / 2 - m_name.getGlobalBounds().width / 2, m_data->window.getSize().y / 2 - m_name.getGlobalBounds().height * 5);
							}
							else
							{
								name += static_cast<char>(evnt.text.unicode);
								m_name.setString("Dein Name lautet: " + name);
								m_name.setPosition(m_data->window.getSize().x / 2 - m_name.getGlobalBounds().width / 2, m_data->window.getSize().y / 2 - m_name.getGlobalBounds().height * 5);
							}
						}
					}
				}
			}			
		}
		return true;
	}

	bool MainMenuState::Update(float dt)
	{	
		if (m_data->input.IsCursorOnSprite(m_Button, m_data->window)) //Hover-Event
		{
			m_Button.setTextureRect(sf::IntRect(64, 0, 64, 32));
			if (!IsFocussedSoundPlayed)
			{
				m_FocussedSound.play();
				IsFocussedSoundPlayed = true;
			}
			if (m_data->input.IsSpriteClicked(m_Button, sf::Mouse::Left, m_data->window)) //Clickevent
			{
				m_Button.setTextureRect(sf::IntRect(128, 0, 64, 32));
				if (m_Clock.getElapsedTime().asSeconds() > 0.2f) //Delay
				{
					if (!EingabeLäuft)
					{
						m_ButtonText.setString("Stop");
						m_ButtonText.setPosition(m_Button.getPosition().x + m_Button.getGlobalBounds().width / 2 - m_ButtonText.getGlobalBounds().width / 2, m_Button.getPosition().y + m_Button.getGlobalBounds().height / 2 - m_ButtonText.getGlobalBounds().height / 1.5f);
						EingabeLäuft = true;
					}
					else
					{
						m_ButtonText.setString("Start");
						m_ButtonText.setPosition(m_Button.getPosition().x + m_Button.getGlobalBounds().width / 2 - m_ButtonText.getGlobalBounds().width / 2, m_Button.getPosition().y + m_Button.getGlobalBounds().height / 2 - m_ButtonText.getGlobalBounds().height / 1.5f);
						rw->Write(name, "Resources/data/name.txt", true);
						EingabeLäuft = false;
					}
					m_Clock.restart();
				}				
				if (!IsKlickSoundPlayed)
				{
					m_KlickSound.play();
					IsKlickSoundPlayed = true;
				}
			}
			else
			{
				IsKlickSoundPlayed = false;
			}
		}
		else
		{
			m_Button.setTextureRect(sf::IntRect(0, 0, 64, 32));
			IsFocussedSoundPlayed = false;
		}

		return true;
	}

	bool MainMenuState::Render(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_Button);
		m_data->window.draw(m_ButtonText);
		m_data->window.draw(m_Aufforderung);
		m_data->window.draw(m_name);
		
		m_data->window.display();
		return true;
	}
}