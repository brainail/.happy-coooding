#include "GColor.h"

void GColor::SetColor(GLfloat aR, GLfloat aG, GLfloat aB, GLfloat aAlpha)
{
	r = aR, g = aG, b = aB, alpha = aAlpha;
}

GColor::GColor(GLfloat aR, GLfloat aG, GLfloat aB, GLfloat aAlpha)
{
	r = aR, g = aG, b = aB, alpha = aAlpha;
}

GColor::~GColor()
{
}
