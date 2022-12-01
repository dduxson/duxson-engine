#include "./Include/LineWidth.h"

using namespace DE;

LineWidth::LineWidth(float width)
	: IRenderState()
	, m_width(width)
{

}

void LineWidth::enable() const
{
	glLineWidth(m_width);
}

void LineWidth::disable() const
{
	glLineWidth(1.0f);
}