#ifndef GColor_H_Included
#define GColor_H_Included

#include <gl\gl.h>

class GColor
{
 	public:
		GColor(GLfloat aR = 0.0f, GLfloat aG = 0.0f, GLfloat aB = 0.0f, GLfloat aAlpha = 0.0f);
		virtual ~GColor();

  		void SetColor(GLfloat aR = 0.0f, GLfloat aG = 0.0f, GLfloat aB = 0.0f, GLfloat aAlpha = 0.0f);

	public:
		GLfloat r, g, b, alpha;
};

#endif
