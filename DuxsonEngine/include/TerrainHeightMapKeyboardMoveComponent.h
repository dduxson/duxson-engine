/*!********************************************************************
* File:	TerrainHeightMapKeyboardMoveComponent.h
*
* \brief	Component that can be attached to an entity to move it
*			about using the keyboard that will automatically take the
*			height of the terrain. It will also not allow you to move
*			outside the terrain bounds.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include "KeyboardMoveComponent.h"
#include "TerrainHeightMapComponent.h"

namespace DE
{
	class TerrainHeightMapKeyboardMoveComponent : public KeyboardMoveComponent
	{
		public:
			TerrainHeightMapKeyboardMoveComponent(TerrainHeightMapComponent::SPtr terrainHeightMapComponent, float heightAboveTerrain = 2.0f, float speed = 10.0f, sf::Keyboard::Key forwardKey = sf::Keyboard::W,
													sf::Keyboard::Key backKey = sf::Keyboard::S, sf::Keyboard::Key rightKey = sf::Keyboard::D,
													sf::Keyboard::Key leftKey = sf::Keyboard::A);

			virtual ~TerrainHeightMapKeyboardMoveComponent();

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);
			virtual void render(IVisualEngine::SPtr visualEngine) const;

		private:
			TerrainHeightMapComponent::WPtr m_terrainHeightMapComponent;
			float m_heightAboveTerrain;
	};
}