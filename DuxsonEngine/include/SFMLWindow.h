/*!********************************************************************
 * File:	SFMLWindow.h										
 *
 * \brief	Class that represents a window in the Duxson engine.
 * \details This class uses SFML for window creation and management and
 *			is a wrapper around the window class of SFML.
 *
 * \author	David Duxson
 *
 * \date	04/10/2015
 *
 **********************************************************************/
#pragma once

#include "IWindow.h"
#include "IInput.h"
#include "SFMLWindowSettings.h"

namespace DE
{
	class SFMLWindow : public IWindow
	{
		public:
			/*!
			 *	\brief	Constructor for SFMLWindow class.
			 *	\param[in] _input The input that this window should update
			 *	\param[in] _settings The SFMLWindow settings
			 */
			SFMLWindow(IInput::SPtr _input, const SFMLWindowSettings& _settings = SFMLWindowSettings("Duxson Engine"));

			/*!
			 *	\brief	Destructor for SFMLWindow class.
			 */
			virtual ~SFMLWindow();

			/*!
			 *	\see IWindow
			 */
			void update();

			/*!
			*	\see IWindow
			*/
			void swapBuffers();

			/*!
			*	\see IWindow
			*/
			bool isOpen() const;

			/*!
			*	\see IWindow
			*/
			unsigned int getWidth() const;

			/*!
			*	\see IWindow
			*/
			unsigned int getHeight() const;

			/*!
			*	\see IWindow
			*/
			float getAspect() const;

			/*!
			*	\see IWindow
			*/
			glm::vec2 getCentre() const;

			/*!
			*	\see IWindow
			*/
			void forceMousePosition(const glm::vec2& mousePos);

			/*!
			*	\see IWindow
			*/
			void setCursorVisibility(bool visible);

			/*!
			*	\see IWindow
			*/
			void closeWindow();

			/*!
			*	\brief	Returns the OpenGL context settings the window has.
			*	\return ContextSettings structure for OpenGL.
			*/
			sf::ContextSettings getContextSettings() const;

		private:
			/*!
			 *	\brief	Initialises GLEW
			 *	\remark Called from constructors.
			 */
			void initGLEW();

		private:
			sf::Window		m_window;				///< The SFML window this class uses.
			IInput::SPtr	m_input;				///< Pointer to the input for this window (handles at least mouse and keyboard)
	};
}