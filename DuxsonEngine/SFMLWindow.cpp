#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "./Include/SFMLWindow.h"
#include "./Include/Logger.h"
#include "./Include/IInput.h"
#include <iostream>

namespace DE
{
	SFMLWindow::SFMLWindow(IInput::SPtr _input, const SFMLWindowSettings& _settings)
		: m_window(_settings.videoMode, sf::String(_settings.title), _settings.windowFlags, _settings.contextSettings)
		, m_input(_input)
	{
		if (_settings.setWidthAndHeight)
			m_window.setSize(sf::Vector2u(_settings.width, _settings.height));

		m_window.setVerticalSyncEnabled(_settings.verticalSync);

		initGLEW();
	}

	SFMLWindow::~SFMLWindow()
	{
		m_window.close();
	}

	void SFMLWindow::initGLEW()
	{
		if (glewInit() != GLEW_OK)
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to initialse Glew.");
		else
			Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Sucessfully initialised Glew.");

		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "OpenGL Version: %d.%d",
			getContextSettings().majorVersion,
			getContextSettings().minorVersion);
	}

	void SFMLWindow::update()
	{
		// handle events
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::LostFocus:
				m_input->clearAllKeysAndBtns();
				break;
			case sf::Event::KeyPressed:
				m_input->setKey(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				m_input->setKey(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				m_input->setMouseBtn(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				m_input->setMouseBtn(event.mouseButton.button, false);
				break;
			case sf::Event::MouseMoved:
				m_input->setMousePos(event.mouseMove.x, event.mouseMove.y);
				break;
			}
		}
	}

	void SFMLWindow::swapBuffers()
	{
		m_window.display();
	}

	bool SFMLWindow::isOpen() const
	{
		return m_window.isOpen();
	}

	unsigned int SFMLWindow::getWidth() const
	{
		return m_window.getSize().x;
	}

	unsigned int SFMLWindow::getHeight() const
	{
		return m_window.getSize().y;
	}

	float SFMLWindow::getAspect() const
	{
		return (float(getWidth()) / float(getHeight()));
	}

	glm::vec2 SFMLWindow::getCentre() const
	{
		return glm::vec2(float(getWidth()) / 2.0f, float(getHeight()) / 2.0f);
	}

	void SFMLWindow::forceMousePosition(const glm::vec2& mousePos)
	{
		sf::Mouse::setPosition(sf::Vector2i(int(mousePos.x), int(mousePos.y)), m_window);
	}

	void SFMLWindow::setCursorVisibility(bool visible)
	{
		m_window.setMouseCursorVisible(visible);
	}

	void SFMLWindow::closeWindow()
	{
		m_window.close();
	}

	sf::ContextSettings SFMLWindow::getContextSettings() const
	{
		return m_window.getSettings();
	}
}