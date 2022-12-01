#include "./Include/Blending.h"

namespace DE
{
	Blending::Blending()
		: IRenderState()
		, enabled(false)
		, sfactor(GL_SRC_ALPHA)
		, dfactor(GL_ONE_MINUS_SRC_ALPHA)
	{

	}
	Blending::Blending(bool _enabled)
		: IRenderState()
		, enabled(_enabled)
		, sfactor(GL_SRC_ALPHA)
		, dfactor(GL_ONE_MINUS_SRC_ALPHA)
	{

	}
	Blending::Blending(bool _enabled, GLenum _sfactor, GLenum _dfactor)
		: IRenderState()
		, enabled(_enabled)
		, sfactor(_sfactor)
		, dfactor(_dfactor)
	{

	}

	void Blending::enable() const
	{
		if (enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(sfactor, dfactor);
		}
	}

	void Blending::disable() const
	{
		if (enabled)
			glDisable(GL_BLEND);
	}
}