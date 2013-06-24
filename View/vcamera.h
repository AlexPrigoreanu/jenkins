#ifndef VCAMERA_H
#define VCAMERA_H

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")

#include <windows.h>					// Header File For Windows
#include <gl\gl.h>						// Header File For The OpenGL32 Library
#include <gl\glu.h>						// Header File For The GLU32 Library
#include <math.h>

#define CAMERASPEED	0.03f				// The Camera Speed

struct tVector3	// Extended 3D Vector Struct
{
    tVector3() {} // Struct Constructor
    tVector3 (float new_x, float new_y, float new_z) // Init Constructor
    { x = new_x; y = new_y; z = new_z; }

    tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
    tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
    tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
    tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}

    float x, y, z;						// 3D vector coordinates
};

class CCamera
{
    public:

        tVector3 mPos;
        tVector3 mView;
        tVector3 mUp;

        void Strafe_Camera(float speed, bool YAxis);
        void Mouse_Move(int wndWidth, int wndHeight);
        void Move_Camera(float speed);
        void Rotate_View(float speed);
        void Position_Camera(float pos_x, float pos_y,float pos_z,
                             float view_x, float view_y, float view_z,
                             float up_x,   float up_y,   float up_z);
};

#endif // VCAMERA_H
