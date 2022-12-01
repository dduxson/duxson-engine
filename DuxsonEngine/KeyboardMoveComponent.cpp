#include "./Include/KeyboardMoveComponent.h"
#include "./include/VisualEngine.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace DE
{

	KeyboardMoveComponent::KeyboardMoveComponent(float speed, sf::Keyboard::Key forwardKey,
		sf::Keyboard::Key backKey, sf::Keyboard::Key rightKey,
		sf::Keyboard::Key leftKey)
		: VisualEntityComponent()
		, m_speed(speed)
		, m_forward(forwardKey)
		, m_back(backKey)
		, m_right(rightKey)
		, m_left(leftKey)
	{

	}

	KeyboardMoveComponent::~KeyboardMoveComponent()
	{

	}

	void KeyboardMoveComponent::update(IVisualEngine::SPtr visualEngine, float dtSecs)
	{
		if (visualEngine != nullptr && visualEngine->getUtilities().getWindow() != nullptr && (!m_parent.expired()))
		{
			IInput::SPtr input = visualEngine->getUtilities().getInput();

			const Transform& transform = m_parent.lock()->getTransform();

			//Get the forward and right vectors.
			glm::vec3 forwardDir = transform.getForwardDir();
			glm::vec3 rightDir = transform.getRightDir();
			glm::vec3 upDir = transform.getUpDir();

			//Now compose a translation and apply it.
			glm::vec3 translation(0,0,0);

			if (input)
			{
				if (input->isKeyPressed(m_forward))
					translation += m_speed * dtSecs * forwardDir;
				if (input->isKeyPressed(m_back))
					translation -= m_speed * dtSecs * forwardDir;
				if (input->isKeyPressed(m_right))
					translation += m_speed * dtSecs * rightDir;
				if (input->isKeyPressed(m_left))
					translation -= m_speed * dtSecs * rightDir;
				/*if(input->isKeyPressed(sf::Keyboard::I))
				translation += m_speed * dtSecs * upDir;
				if(input->isKeyPressed(sf::Keyboard::K))
				translation -= m_speed * dtSecs * upDir;*/

				if (translation.x != 0 || translation.y != 0 || translation.z != 0)
					m_parent.lock()->setTrans(transform.getTrans() + translation);
			}

			//std::cout << "FIRSTKEY" << transform.getTrans().x << "," << transform.getTrans().y << "," << transform.getTrans().z << "\n";
			//std::cout << m_parent->getWorldTransform().getTrans().x << "," << m_parent->getWorldTransform().getTrans().y << "," << m_parent->getWorldTransform().getTrans().z << "\n";
		}
	}

	void KeyboardMoveComponent::render(IVisualEngine::SPtr visualEngine) const
	{

	}
}