#pragma once

#include "VisualEntityComponent.h"

namespace DE
{
	struct ViewportParams
	{
		public:
			ViewportParams()
			{
				useFullWindow = true;
				x = 0;
				y = 0;
				width = 0;
				height = 0;
			}

			ViewportParams(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height)
			{
				useFullWindow = false;
				x = _x;
				y = _y;
				width = _width;
				height = _height;
			}

			bool useFullWindow;		///< If this is true we ignore other params.
			unsigned int x;			///< The lower left corner x of the viewport rectangle, in pixels.
			unsigned int y;			///< The lower left corner y of the viewport rectangle, in pixels.
			unsigned int width;		///< The width of the viewport rectangle.
			unsigned int height;	///< The height of the viewport rectangle.
	};

	class CameraComponent : public VisualEntityComponent
	{
		public:
			typedef std::shared_ptr<CameraComponent> SPtr;

			CameraComponent(const glm::mat4& projection, const ViewportParams& viewport = ViewportParams());

			virtual ~CameraComponent();

			void setClearMask(unsigned int clearMask);
			void setClearColour(const glm::vec4& clearColour);
			void setRenderOrder(RenderOrder renderOrder);

			RenderOrder getRenderOrder();

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);
			virtual void render(IVisualEngine::SPtr visualEngine) const;

		private:
			glm::mat4		m_projMatrix;
			ViewportParams	m_viewPortParams;
			glm::vec4		m_clearColour;
			unsigned int	m_clearBitMask;
			RenderOrder		m_renderOrder;
	};
}