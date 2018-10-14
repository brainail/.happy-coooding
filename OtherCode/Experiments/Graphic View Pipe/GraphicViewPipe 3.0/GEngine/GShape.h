#ifndef GShape_H_Included
#define GShape_H_Included

#include "GObject.h"
#include "GColor.h"

class GShape: public GObject
{
	public:
		virtual ~GShape();

		void SetColor(GLfloat aR = 0.0f, GLfloat aG = 0.0f, GLfloat aB = 0.0f, GLfloat aAlpha = 0.0f);

		virtual void Draw() = 0;

	public:
		GColor color;
};

#endif
