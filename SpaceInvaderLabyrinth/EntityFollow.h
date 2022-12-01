#pragma once
/*!********************************************************************
*	File:	EntityFollow.h
*
* \brief	This class updates the parent entity to
*			represent a different entity's transformation matrix.
* \details There are scalars and offsets that are configurable. This
*			means the transformation does not have to be the other
*			entities exact transformation matrix.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "../DuxsonEngine/Include/VisualEntityComponent.h"
#include "../DuxsonEngine/include/Entity.h"

class EntityFollow : public DE::VisualEntityComponent
{
	public:
		typedef std::shared_ptr<EntityFollow> SPtr;

		/*!
		*	\brief		Constructor for EntityFollow class.
		*	\param[in]	entity The entity that will be used to update the parent
		*				of this component.
		*/
		EntityFollow(DE::Entity::SPtr entity);

		/*!
		*	\brief		Destructor for EntityFollow class.
		*/
		~EntityFollow();

		/*!
		*	\brief		Sets the scalar to multiply the position by.
		*	\param[in]	scalar A vec3 with the values to multiply the position by.
		*/
		void setPositionScalar(const glm::vec3& scalar);

		/*!
		*	\brief		Sets the scalar to rotation the position by.
		*	\param[in]	scalar A vec3 with the values to multiply the rotation by.
		*/
		void setRotationScalar(const glm::vec3& scalar);

		/*!
		*	\brief		Sets the offset to add to the position after the scalar has
		*				been applied.
		*	\param[in]	offset A vec3 with the values to offset the position by.
		*/
		void setPositionOffset(const glm::vec3& offset);

		/*!
		*	\brief		Sets the offset to add to the rotation after the scalar has
		*				been applied.
		*	\param[in]	offset A vec3 with the values to offset the rotation by. (rads)
		*/
		void setRotationOffset(const glm::vec3& offset);

		/*!
		*	\brief		Sets the following to 2d. This will map x->x -z->y.
		*	\param[in]	twoD True if should be a 2d following.
		*/
		void setTwoD(bool twoD);

		/*!
		*	\brief		see IVisualEntityComponent
		*/
		virtual void update(DE::IVisualEngine::SPtr visualEngine, float dtSecs);

		/*!
		*	\brief		see IVisualEntityComponent
		*/
		virtual void render(DE::IVisualEngine::SPtr visualEngine) const;

	private:
		DE::Entity::SPtr m_entity;		///< The entity that will be used to update the parent entity.
		glm::vec3 m_posScale;			///< The scalar to multiply the position by.
		glm::vec3 m_rotScale;			///< The scalar to multiply the rotation by.
		glm::vec3 m_posOffset;			///< The offset to add to the position after the scalar has been applied.
		glm::vec3 m_rotOffset;			///< The offset to add to the rotation after the scalar has been applied. (rads)
		bool	  m_twoD;				///< Whether the following is 2d or 3d.
};