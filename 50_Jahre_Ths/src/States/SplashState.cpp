#include <iostream>
#include "SplashState.hpp"
#include "../GLOBAL_DEFINITIONS.hpp"


namespace sse
{
	SplashState::SplashState(GameDataRef data)
		: m_data(data)
		, m_pixel_threshold(0.06f)
	{
	}

	bool SplashState::Init()
	{
		m_data->window.setVerticalSyncEnabled(true);
	
		//SplashState loading
		m_data->assets.LoadShaderFile("pixelate", SHADE_PIXELATE_FILEPATH);
		m_data->assets.LoadTexture("logo", LOGO_FILEPATH);

		m_background.setTexture(m_data->assets.GetTexture("logo"));
		m_data->assets.GetShader("pixelate").setUniform("texture", sf::Shader::CurrentTexture);
		m_background.setScale({ (float)m_data->window.getSize().x / m_data->assets.GetTexture("logo").getSize().x, (float)m_data->window.getSize().y / m_data->assets.GetTexture("logo").getSize().y });
		return true;
	}

	bool SplashState::HandleInput(float dt)
	{
		sf::Event event;

		
		while (m_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_data->window.close();
			}
		}
		return true;
	}

	bool SplashState::Update(float dt)
	{
		if (m_pixel_threshold > 0.0f)
		{
			m_pixel_threshold -= 0.025f * dt;
		}
		else
		{
			m_pixel_threshold = 0.0f;
		}
		
		m_data->assets.GetShader("pixelate").setUniform("pixel_threshold", m_pixel_threshold);

		return true;
	}

	bool SplashState::Render(float dt)
	{
		m_data->window.clear(sf::Color::White);

		m_data->window.draw(m_background, &m_data->assets.GetShader("pixelate"));

		m_data->window.display();
		return true;
	}
}