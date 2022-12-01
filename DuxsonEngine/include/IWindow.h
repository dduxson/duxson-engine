/*!********************************************************************
* File:	IWindow.h
*
* \brief	Interface that represents a window in the Duxson engine.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include <memory>
#include <glm/vec2.hpp>

namespace DE
{
	class IWindow
	{
		public:
			typedef std::shared_ptr<IWindow> SPtr;

			/*!
			*	\brief	Default constructor for IWindow class.
			*/
			IWindow() {};

			/*!
			*	\brief	Destructor for IWindow class.
			*/
			virtual ~IWindow() {}

			/*!
			*	\brief	Should be called when you want to process events such
			*			as key presses, mouse clickes, window closing or resizing etc.
			*/
			virtual void update() = 0;

			/*!
			*	\brief	By default this window's context uses double buffering. When
			*			you want to swap what buffer is shown then call this function.
			*/
			virtual void swapBuffers() = 0;

			/*!
			*	\brief	Returns true if the window is open.
			*	\return True if the window is open, false otherwise.
			*/
			virtual bool isOpen() const = 0;

			/*!
			*	\brief	Returns the width of the window in pixels.
			*	\return Width of the window in pixels.
			*/
			virtual unsigned int getWidth() const = 0;

			/*!
			*	\brief	Returns the height of the window in pixels.
			*	\return Height of the window in pixels.
			*/
			virtual unsigned int getHeight() const = 0;

			/*!
			*	\brief	Returns the aspect ratio of the window (width/height)
			*	\return Aspect ratio of window as a float.
			*/
			virtual float getAspect() const = 0;

			/*!
			*	\brief	Returns the centre coordinate of the window.
			*	\return Vec2 representing centre of the window
			*/
			virtual glm::vec2 getCentre() const = 0;

			/*!
			*	\brief	Forces the mouse cursor into a certain position of the window.
			*	\param[in] mousePos The position to force the mouse into of the window.
			*/
			virtual void forceMousePosition(const glm::vec2& mousePos) = 0;

			/*!
			*	\brief	Sets the mouse cursor to either be visible or invisible.
			*	\param[in] visible True if the cursor should be visible, false otherwise.
			*/
			virtual void setCursorVisibility(bool visible) = 0;

			/*!
			*	\brief	Closes the window.
			*/
			virtual void closeWindow() = 0;
	};
}