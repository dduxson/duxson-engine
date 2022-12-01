#pragma once
/*!********************************************************************
*	File:	LivingEntityComponent.h
*
* \brief	Represents an entity that is alive (i.e it has a certain
*			level of health.)
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "MazeEntityComponent.h"

class LivingEntityComponent : public MazeEntityComponent
{
	public:
		/*!
		*	\brief	Constructor for LivingEntityComponent class.
		*/
		LivingEntityComponent();

		/*!
		*	\brief	Destructor for LivingEntityComponent class.
		*/
		virtual ~LivingEntityComponent();

		/*!
		*	\brief	Change the health by the amount specified.
		*	\param[in] health The amount of health that should be added/subtracted
		*					  from this entity. (negative decreases health, positive
		*					  increases health).
		*	\remark	Health level will be clamped between 0 and max health.
		*/
		void changeToHealth(float health);

		/*!
		*	\brief	Sets the maximum health this LivingEntity is allowed.
		*	\param[in] maxHealth	The maximum amount of health that this entity can
		*							have.
		*/
		void setMaxHealth(float maxHealth);

		/*!
		*	\brief	Sets the health to its maximum value.
		*/
		void restoreFullHealth();

		/*!
		*	\brief	Sets health to zero. (Kills this entity).
		*/
		void killEntity();

		/*!
		*	\brief	Gets the health level that this entity has.
		*	\return Health level of this entity.
		*/
		float getHealth();

		/*!
		*	\brief	Checks whether this entity has non zero health.
		*	\return True if non zero health, false otherwise.
		*/
		bool isAlive();

		/*!
		*	\brief	Calculates how long this entity has been dead for.
		*	\return Time this entity has been dead for - will be zero
		*			if the entity is still alive.
		*/
		float getTimeDead();

		/*!
		* \see IVisualEntityComponent
		*/
		virtual void update(DE::IVisualEngine::SPtr visualEngine, float dtSecs);

	private:
		float m_maxHealth;	///< The maximum amount of health this entity can have.
		float m_health;		///< The health this entity currently has.

		float m_secs_dead;	///< The seconds this entity has been dead.
};