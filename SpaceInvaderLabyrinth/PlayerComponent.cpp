#include "PlayerComponent.h"
#include "CollisionSystem.h"
//#include "Invader.h"

PlayerComponent::PlayerComponent(sf::Keyboard::Key forwardKey,
	sf::Keyboard::Key backKey, sf::Keyboard::Key rightKey,
	sf::Keyboard::Key leftKey)
	: LivingEntityComponent()
	, m_forward(forwardKey)
	, m_back(backKey)
	, m_right(rightKey)
	, m_left(leftKey)
{
	setCollidableWithEntites(false);
}

PlayerComponent::~PlayerComponent()
{

}

bool PlayerComponent::setCurrentLocation(glm::vec3 loc, bool checkForCollisions)
{
	bool success = MazeEntityComponent::setCurrentLocation(loc, checkForCollisions);

	DE::IEntity::SPtr parent = m_parent.lock();

	if (parent && getCollisionSystem())
	{
		std::list<DE::IEntity::SPtr> intersectors = getCollisionSystem()->doesEntityIntersectOthers(parent);

		for (std::list<DE::IEntity::SPtr>::iterator itr = intersectors.begin(); itr != intersectors.end(); ++itr)
		{
			/*Invader* invader = dynamic_cast<Invader*>(*itr);
			if( invader )
			{
			//Kill the player - space invader on top of them!
			killEntity();
			break;
			}*/
		}
	}

	return success;
}

void PlayerComponent::update(DE::IVisualEngine::SPtr visualEngine, float dtSecs)
{
	LivingEntityComponent::update(visualEngine, dtSecs);

	DE::IEntity::SPtr parent = m_parent.lock();

	if (parent && visualEngine && visualEngine->getUtilities().getWindow())
	{
		DE::IInput::SPtr input = visualEngine->getUtilities().getInput();

		const DE::Transform& transform = parent->getTransform();

		//Get the forward and right vectors.
		glm::vec3 forwardDir = transform.getForwardDir();
		glm::vec3 rightDir = transform.getRightDir();
		glm::vec3 upDir = transform.getUpDir();

		//Now compose a translation and apply it.
		glm::vec3 translation;

		if (input)
		{
			if (input->isKeyPressed(m_forward))
				translation += getSpeed() * dtSecs * forwardDir;
			if (input->isKeyPressed(m_back))
				translation -= getSpeed() * dtSecs * forwardDir;
			if (input->isKeyPressed(m_right))
				translation += getSpeed() * dtSecs * rightDir;
			if (input->isKeyPressed(m_left))
				translation -= getSpeed() * dtSecs * rightDir;

			translation.y = 0.0f; //Don't allow travel up.

			if (translation.x != 0 || translation.z != 0)
				setCurrentLocation(parent->getWorldTransform().getTrans() + translation);
		}
	}
}

DE::BoundingBox PlayerComponent::boundingBox() const
{
	if (getMazeIn() != NULL)
	{
		float halfBox = (getMazeIn()->getMazeCellLength() / 4.0f) / 2.0f;
		float halfBoxHeight = getMazeIn()->getMazeWallHeight() / 2.0f;

		return DE::BoundingBox(glm::vec3(-halfBox, -halfBoxHeight, -halfBox), glm::vec3(halfBox, halfBoxHeight, halfBox));
	}
	else
	{
		return DE::BoundingBox(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	}
}