#pragma once

#include "IRenderState.h"

namespace DE
{
	class PrimitiveRestart : public IRenderState
	{
	public:
		PrimitiveRestart(unsigned int primitiveRestart);

		void enable() const;
		void disable() const;

	private:
		unsigned int m_primitiveRestart;
	};
}