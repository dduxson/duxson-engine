#include "./Include/PrimitiveRestart.h"
#include <GL/glew.h>

using namespace DE;

PrimitiveRestart::PrimitiveRestart(unsigned int primitiveRestart)
	: IRenderState()
	, m_primitiveRestart(primitiveRestart)
{

}

void PrimitiveRestart::enable() const
{
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(m_primitiveRestart);
}

void PrimitiveRestart::disable() const
{
	glDisable(GL_PRIMITIVE_RESTART);
}