#include "LivingEntityComponent.h"

LivingEntityComponent::LivingEntityComponent()
	: m_maxHealth(100.0f)
	, m_health(100.0f)
{

}

LivingEntityComponent::~LivingEntityComponent()
{

}

void LivingEntityComponent::changeToHealth(float health)
{
	m_health += health;

	//Clamp.
	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
	else if (m_health < 0.0f)
		killEntity();
}

void LivingEntityComponent::setMaxHealth(float maxHealth)
{
	m_maxHealth = maxHealth;
}

void LivingEntityComponent::restoreFullHealth()
{
	m_health = m_maxHealth;
}

void LivingEntityComponent::killEntity()
{
	m_health = 0.0f;
}

float LivingEntityComponent::getHealth()
{
	return m_health;
}

bool LivingEntityComponent::isAlive()
{
	return m_health > 0.0f;
}

float LivingEntityComponent::getTimeDead()
{
	if (isAlive())
		return 0.0f;

	return m_secs_dead;
}

void LivingEntityComponent::update(DE::IVisualEngine::SPtr visualEngine, float dtSecs)
{
	if (isAlive())
		m_secs_dead = 0.0f;
	else
		m_secs_dead += dtSecs;
}