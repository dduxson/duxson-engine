#pragma once

#include "IWindow.h"
#include "IInput.h"
#include "IUpdateVisualEntityVisitor.h"
#include "IRenderVisualEntityVisitor.h"
//#include "IFontHandler.h"

namespace DE
{
	class VisualEngineUtilities
	{
		public:
			VisualEngineUtilities(IWindow::SPtr window, IInput::SPtr input, IUpdateVisualEntityVisitor::SPtr updateVisitor, IRenderVisualEntityVisitor::SPtr renderVisitor)
				: m_window(window), m_input(input), m_updateVisitor(updateVisitor), m_renderVisitor(renderVisitor)
			{}

			VisualEngineUtilities(const VisualEngineUtilities& other)
				: m_window(other.m_window), m_input(other.m_input), m_updateVisitor(other.m_updateVisitor), m_renderVisitor(other.m_renderVisitor)
			{}

			VisualEngineUtilities() {}

			IWindow::SPtr getWindow() { return m_window; }
			IInput::SPtr getInput() { return m_input; }
			IUpdateVisualEntityVisitor::SPtr getUpdateVisitor() { return m_updateVisitor; }
			IRenderVisualEntityVisitor::SPtr getRenderVisitor() { return  m_renderVisitor; }

		private:
			IWindow::SPtr m_window;
			IInput::SPtr m_input;
			IUpdateVisualEntityVisitor::SPtr m_updateVisitor;
			IRenderVisualEntityVisitor::SPtr m_renderVisitor;
			//IFontHandler::SPtr m_textHandler;
	};
}