/*!********************************************************************
* File:	Input.h
*
* \brief	Interface that handles basic input from a keyboard and
*			and mouse for the Duxson Engine
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <glm/vec2.hpp>

namespace DE
{
	class IInput
	{
		public:
			typedef std::shared_ptr<IInput> SPtr;

			/*!
			*	\brief	Constructor for IInput class.
			*/
			IInput() {}

			/*!
			*	\brief	Destructor for IInput class.
			*/
			virtual ~IInput() {}

			/*!
			*	\brief	Sets whether a key is pressed or not.
			*	\param[in] keycode	Integer code of the key.
			*	\param[in] pressed	Should be set to true if pressed, false otherwise.
			*/
			virtual void setKey(int keyCode, bool pressed) = 0;

			/*!
			*	\brief	Sets whether a mouse button is pressed or not.
			*	\param[in] mouseBtnCode	Integer code of the mouse button.
			*	\param[in] pressed	Should be set to true if pressed, false otherwise.
			*/
			virtual void setMouseBtn(int mouseBtnCode, bool pressed) = 0;

			/*!
			*	\brief	Sets the current stored position of the mouse.
			*	\param[in] keycode	x coordinate (pixel space)
			*	\param[in] pressed	y coordinate (pixel space)
			*/
			virtual void setMousePos(int x, int y) = 0;

			/*!
			*	\brief	Gets whether a key is currently pressed.
			*	\param[in] keycode	Integer code of the key.
			*	\return True if key is pressed, false otherwise (false if keycode invalid)
			*/
			virtual bool isKeyPressed(int keyCode) const = 0;

			/*!
			*	\brief	Gets whether a mouse button is currently pressed.
			*	\param[in] mouseBtnCode	Integer code of the mouse button.
			*	\return True if button is pressed, false otherwise (false if code invalid)
			*/
			virtual bool isMouseBtnPressed(int mouseBtnCode) const = 0;

			/*!
			*	\brief	Gets the current stored position of the mouse.
			*	\return Vec2 of mouse position in pixel space.
			*/
			virtual glm::vec2 getMousePos() = 0;

			/*!
			*	\brief	Sets all btns and keys to not being pressed.
			*	\remark Useful if window goes out of focus.
			*/
			virtual void clearAllKeysAndBtns() = 0;
	};
}