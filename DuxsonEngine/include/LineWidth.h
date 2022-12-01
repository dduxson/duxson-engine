#pragma once

#include "IRenderState.h"
#include <GL/glew.h>

namespace DE
{
	class LineWidth : public IRenderState
	{
	public:
		LineWidth(float width);

		void enable() const;
		void disable() const;

	private:
		float m_width;
	};
}