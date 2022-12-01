#pragma once
/*!********************************************************************
*	File:	Player.h
*
* \brief	Represents a player in the maze.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "LivingEntityComponent.h"
#include "SFML/Window/Keyboard.hpp"

class PlayerComponent : public LivingEntityComponent
{
	public:
		typedef std::shared_ptr<PlayerComponent> SPtr;

		/*!
		*	\brief	Constructor for Player class.
		*/
		PlayerComponent(sf::Keyboard::Key forwardKey = sf::Keyboard::W,
			sf::Keyboard::Key backKey = sf::Keyboard::S, sf::Keyboard::Key rightKey = sf::Keyboard::D,
			sf::Keyboard::Key leftKey = sf::Keyboard::A);

		/*!
		*	\brief	Destructor for Player class.
		*/
		virtual ~PlayerComponent();

		/*!
		*	\brief	Calls base version and then will check if an enemy has
		*			intersected with us. If so, we kill this player!
		*/
		bool setCurrentLocation(glm::vec3 loc, bool checkForCollisions = true);

		/*!
		* \see IVisualEntityComponent
		*/
		virtual void update(DE::IVisualEngine::SPtr visualEngine, float dtSecs);

		/*!
		* \see IVisualEntityComponent
		*/
		virtual DE::BoundingBox boundingBox() const;

	private:
		sf::Keyboard::Key m_forward;
		sf::Keyboard::Key m_back;
		sf::Keyboard::Key m_right;
		sf::Keyboard::Key m_left;
};