#pragma once
class Attenuation
{
	public:
		Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
			m_constant(constant),
			m_linear(linear),
			m_exponent(exponent) {}

		inline float getConstant() const { return m_constant; }
		inline float getLinear()   const { return m_linear; }
		inline float getExponent() const { return m_exponent; }

	private:
		float m_constant;
		float m_linear;
		float m_exponent;
};