#ifndef GCubeGrid_H_Included
#define GCubeGrid_H_Included

#include "GShape.h"

class GCubeGrid: public GShape 
{
	public:
		virtual ~GCubeGrid();

		void Draw();

		void SetSize(GLfloat aSize = 0.0f);
		void SetMeasure(GLfloat aMeasure = 1.0f);

	public:
		GLfloat size;
		GLfloat measure;
};

#endif 
