#include "./Include/TerrainHeightMapKeyboardMoveComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "include\TerrainHeightMapKeyboardMoveComponent.h"

namespace DE
{
	TerrainHeightMapKeyboardMoveComponent::TerrainHeightMapKeyboardMoveComponent(TerrainHeightMapComponent::SPtr terrainHeightMapComponent, float heightAboveTerrain, float speed,
																				sf::Keyboard::Key forwardKey, sf::Keyboard::Key backKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key leftKey)
		: KeyboardMoveComponent(speed, forwardKey, backKey, rightKey, leftKey),
		m_terrainHeightMapComponent(terrainHeightMapComponent),
		m_heightAboveTerrain(heightAboveTerrain)
	{

	}

	TerrainHeightMapKeyboardMoveComponent::~TerrainHeightMapKeyboardMoveComponent()
	{

	}

	void TerrainHeightMapKeyboardMoveComponent::update(IVisualEngine::SPtr visualEngine, float dtSecs)
	{
		if ((!m_parent.expired()) && (!m_terrainHeightMapComponent.expired()))
		{
			IEntity::SPtr parent_ptr = m_parent.lock();
			//Store original transform information
			Transform orig_transform = parent_ptr->getTransform();

			//Update in the usual way ignoring height.
			KeyboardMoveComponent::update(visualEngine, dtSecs);

			Transform new_world_transform = parent_ptr->getWorldTransform();
			glm::vec3 translation = parent_ptr->getTransform().getTrans();
			glm::vec3 world_translation = new_world_transform.getTrans();

			//Now set height from terrain height map.
			double height = m_terrainHeightMapComponent.lock()->getWorldHeight(world_translation.x, world_translation.z);

			if (height >= 0.0f)
				parent_ptr->setTrans(glm::vec3(translation.x, height + m_heightAboveTerrain, translation.z));
			else
				parent_ptr->setTrans(orig_transform.getTrans());
		}
	}

	void TerrainHeightMapKeyboardMoveComponent::render(IVisualEngine::SPtr visualEngine) const
	{
	}
}