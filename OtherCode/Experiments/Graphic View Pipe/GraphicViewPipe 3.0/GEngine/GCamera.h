#ifndef GCamera_H_Included
#define GCamera_H_Included

#include "GObject.h"

class GCamera: public GObject
{
	public:
		virtual ~GCamera();

		void UpdatePosition(const bool keyDown[]);
  		void SetView();

    public:
        const static GLfloat cameraSpeed = 0.0035f * 40.0f;
};

#endif
