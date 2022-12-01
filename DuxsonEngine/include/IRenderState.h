#pragma once
#include <memory>

namespace DE
{
	class IRenderState
	{
		public:
			typedef std::shared_ptr<IRenderState> SPtr;

			IRenderState() {};
			virtual ~IRenderState() {};

			virtual void enable() const = 0;
			virtual void disable() const = 0;
	};
}