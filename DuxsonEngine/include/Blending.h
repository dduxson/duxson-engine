#pragma once

#include "IRenderState.h"
#include <GL/glew.h>

namespace DE
{
	class Blending : public IRenderState
	{
	public:
		Blending();
		Blending(bool _enabled);
		Blending(bool _enabled, GLenum _sfactor, GLenum _dfactor);

		void enable() const;
		void disable() const;

	private:
		bool enabled;
		GLenum sfactor;
		GLenum dfactor;
	};
}