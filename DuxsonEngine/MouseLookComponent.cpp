#include "./Include/MouseLookComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

namespace DE
{
	MouseLookComponent::MouseLookComponent(float horizontalAngle, float verticalAngle, float sensitivity)
		: VisualEntityComponent()
		, m_sensitivity(sensitivity)
		, m_firstTime(true)
		, m_verticalAngle(horizontalAngle)
		, m_horizontalAngle(verticalAngle)
	{

	}

	MouseLookComponent::~MouseLookComponent()
	{

	}

	void MouseLookComponent::update(IVisualEngine::SPtr visualEngine, float dtSecs)
	{
		if (visualEngine != nullptr && visualEngine->getUtilities().getWindow() != nullptr && (!m_parent.expired()))
		{
			glm::vec2 windowCentre = visualEngine->getUtilities().getWindow()->getCentre();
			const Transform& transform = m_parent.lock()->getTransform();

			//std::cout << transform.getTrans().x << "," << transform.getTrans().y << "," << transform.getTrans().z << "\n";

			//Be careful - the first time we just want to set the mouse into position.
			if (!m_firstTime)
			{
				IInput::SPtr input = visualEngine->getUtilities().getInput();

				glm::vec2 deltaPos = input->getMousePos() - windowCentre;

				float width = float(visualEngine->getUtilities().getWindow()->getWidth());
				float height = float(visualEngine->getUtilities().getWindow()->getHeight());

				bool rotY = (deltaPos.x != 0.0f);
				bool rotX = (deltaPos.y != 0.0f);

				if (rotX || rotY)
				{
					m_horizontalAngle -= (deltaPos.x / width) * glm::pi<float>() * m_sensitivity;
					m_verticalAngle -= (deltaPos.y / height) * glm::pi<float>() * m_sensitivity;

					if (m_verticalAngle > glm::half_pi<float>())
						m_verticalAngle = glm::half_pi<float>();
					if (m_verticalAngle < -glm::half_pi<float>())
						m_verticalAngle = -glm::half_pi<float>();

					m_horizontalAngle = fmod(m_horizontalAngle, 4.0f * glm::pi<float>());

					setNewRotMatrix(transform, m_verticalAngle, m_horizontalAngle);

					visualEngine->getUtilities().getWindow()->forceMousePosition(windowCentre);
				}
			}
			else
			{
				if (m_verticalAngle > glm::half_pi<float>())
					m_verticalAngle = glm::half_pi<float>();
				if (m_verticalAngle < -glm::half_pi<float>())
					m_verticalAngle = -glm::half_pi<float>();

				m_horizontalAngle = fmod(m_horizontalAngle, 2.0f * glm::pi<float>());

				setNewRotMatrix(transform, m_verticalAngle, m_horizontalAngle);

				visualEngine->getUtilities().getWindow()->setCursorVisibility(false);
				visualEngine->getUtilities().getWindow()->forceMousePosition(windowCentre);
				m_firstTime = false;
			}
		}
	}

	void MouseLookComponent::setNewRotMatrix(const Transform& transform, float verticalAngle, float horizontalAngle)
	{
		//Calculate Vectors (Spherical coordinates to Cartesian coordinates conversion)
		glm::vec3 direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle));

		glm::vec3 right = -glm::vec3(sin(horizontalAngle - glm::half_pi<float>()),
			0,
			cos(horizontalAngle - glm::half_pi<float>()));

		glm::vec3 up = glm::cross(direction, right);

		m_parent.lock()->setRot(transform.lookAt(transform.getTrans(), transform.getTrans() + direction, up));

		//glm::quat eA = transform.getRot();
		//glm::quat eAW = m_parent->getWorldTransform().getRot();

		//std::cout << "FIRST" << eA.x << "," << eA.y << "," << eA.z << "," << eA.w << "\n";
		//std::cout << eAW.x << "," << eAW.y << "," << eAW.z << "," << eAW.w << "\n";
	}

	void MouseLookComponent::render(IVisualEngine::SPtr visualEngine) const
	{

	}
}