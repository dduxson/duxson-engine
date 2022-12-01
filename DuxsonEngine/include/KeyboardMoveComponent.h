/*!********************************************************************
* File:	KeyboardMoveComponent.h
*
* \brief	Component that can be attached to an entity to move it
*			about using the keyboard.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include "VisualEntityComponent.h"
#include <SFML/Window.hpp>

namespace DE
{
	class KeyboardMoveComponent : public VisualEntityComponent
	{
		public:
			KeyboardMoveComponent(float speed = 10.0f, sf::Keyboard::Key forwardKey = sf::Keyboard::W,
				sf::Keyboard::Key backKey = sf::Keyboard::S, sf::Keyboard::Key rightKey = sf::Keyboard::D,
				sf::Keyboard::Key leftKey = sf::Keyboard::A);

			virtual ~KeyboardMoveComponent();

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);
			virtual void render(IVisualEngine::SPtr visualEngine) const;

		protected:
			float m_speed;
			sf::Keyboard::Key m_forward;
			sf::Keyboard::Key m_back;
			sf::Keyboard::Key m_right;
			sf::Keyboard::Key m_left;
	};
}