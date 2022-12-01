/*!********************************************************************
 * File:	SFMLInput.h										
 *
 * \brief	Class that handles basic input from a keyboard and mouse
*			that uses the SFML library.
 *
 * \author	David Duxson
 *
 * \date	04/03/2015
 *
 **********************************************************************/
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "IInput.h"

namespace DE
{
	class SFMLInput :public IInput
	{
		public:
			/*!
			 *	\brief	Constructor for SFMLInput class.
			 */
			SFMLInput();

			/*!
			 *	\brief	Destructor for SFMLInput class.
			 */
			virtual ~SFMLInput();

			/*!
			 *	\see IInput
			 */
			void setKey( int keyCode, bool pressed );

			/*!
			*	\see IInput
			*/
			void setMouseBtn( int mouseBtnCode, bool pressed );

			/*!
			*	\see IInput
			*/
			void setMousePos( int x, int y );

			/*!
			*	\see IInput
			*/
			bool isKeyPressed( int keyCode ) const;

			/*!
			*	\see IInput
			*/
			bool isMouseBtnPressed( int mouseBtnCode ) const;

			/*!
			*	\see IInput
			*/
			glm::vec2 getMousePos();

			/*!
			*	\see IInput
			*/
			void clearAllKeysAndBtns();

		private:
			bool m_keysPressed[sf::Keyboard::KeyCount];			///< The state of the keys on the keyboard.
			bool m_mouseBtnPressed[sf::Mouse::ButtonCount];		///< The state of the mouse buttons.
			glm::vec2 m_mousePos;								///< The mouse's current position (in pixel space)
	};
}