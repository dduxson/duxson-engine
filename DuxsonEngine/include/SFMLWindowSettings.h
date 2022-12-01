/*!********************************************************************
* File:	SFMLWindowSettings.h
*
* \brief	Class that represents a window settings for an SFML Window
*			in the Duxson Engine.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include <string>
#include <SFML/Window.hpp>

class SFMLWindowSettings
{
	public:
		bool setWidthAndHeight;					///< Whether we set the height and width with given values
		unsigned int width;						///< Width of window in pixels
		unsigned int height;					///< Height of window in pixels
		std::string title;						///< String representing the title of the window
		bool verticalSync;						///< Should window be vertical synced
		unsigned int windowFlags;				///< The flags for the window (e.g. title bar etc)
		sf::VideoMode videoMode;				///< The video mode the window should have
		sf::ContextSettings contextSettings;	///< The OpenGL context settings (used as guide only)

		/*!
		*	\brief	Constructor for SFMLWindowSettings class.
		*	\param[in] _title The title for the window
		*/
		SFMLWindowSettings(const std::string& _title)
		{
			title = _title;
			setWidthAndHeight = true;
			width = 800;
			height = 600;
			windowFlags = sf::Style::Default;
			verticalSync = true;
			videoMode = sf::VideoMode(width, height);
			contextSettings = sf::ContextSettings(32, 0, 8, 3, 3);
		}
};