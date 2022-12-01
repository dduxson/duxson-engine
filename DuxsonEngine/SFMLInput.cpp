#include "./Include/SFMLInput.h"
#include "./Include/Logger.h"

namespace DE
{
	SFMLInput::SFMLInput()
	{
		clearAllKeysAndBtns();
	}

	SFMLInput::~SFMLInput()
	{

	}

	void SFMLInput::setKey(int keyCode, bool pressed)
	{
		if (keyCode >= 0 && keyCode < sf::Keyboard::KeyCount)
			m_keysPressed[keyCode] = pressed;
		else
			Logger::Instance()->writeToLogFile(Logger::eLogWarning, "Input - Could not set key state as key code supplied was greater than max number of keys.");
	}

	void SFMLInput::setMouseBtn(int mouseBtnCode, bool pressed)
	{
		if (mouseBtnCode >= 0 && mouseBtnCode < sf::Mouse::ButtonCount)
			m_mouseBtnPressed[mouseBtnCode] = pressed;
		else
			Logger::Instance()->writeToLogFile(Logger::eLogWarning, "Input - Could not set mouse button state as mouse button code supplied was greater than max number of mouse buttons.");
	}

	void SFMLInput::setMousePos(int x, int y)
	{
		m_mousePos = glm::vec2(x, y);
	}

	bool SFMLInput::isKeyPressed(int keyCode) const
	{
		if (keyCode >= sf::Keyboard::KeyCount)
			return false;

		return m_keysPressed[keyCode];
	}

	bool SFMLInput::isMouseBtnPressed(int mouseBtnCode) const
	{
		if (mouseBtnCode >= sf::Mouse::ButtonCount)
			return false;

		return m_mouseBtnPressed[mouseBtnCode];
	}

	glm::vec2 SFMLInput::getMousePos()
	{
		return m_mousePos;
	}

	void SFMLInput::clearAllKeysAndBtns()
	{
		memset(m_keysPressed, 0, sizeof(m_keysPressed));
		memset(m_mouseBtnPressed, 0, sizeof(m_mouseBtnPressed));
	}
}