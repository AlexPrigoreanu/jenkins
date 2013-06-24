#include "vcamera.h"
#include <math.h>

void CCamera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
                              float view_x, float view_y, float view_z,
                              float up_x,   float up_y,   float up_z)
{
    mPos	= tVector3(pos_x,  pos_y,  pos_z ); // set position
    mView	= tVector3(view_x, view_y, view_z); // set view
    mUp		= tVector3(up_x,   up_y,   up_z  ); // set the up vector



}



void CCamera::Move_Camera(float speed)
{
    tVector3 vVector = mView - mPos;

    mPos.x  = mPos.x  + vVector.x * speed;
    mPos.z  = mPos.z  + vVector.z * speed;
    mView.x = mView.x + vVector.x * speed;
    mView.z = mView.z + vVector.z * speed;
    mPos.y  = mPos.y  + vVector.y * speed;  //  camera con vettore y attivato (up/down)
    mView.y = mView.y + vVector.y * speed;  //

}


void CCamera::Rotate_View(float speed)
{
    tVector3 vVector = mView - mPos;	// Get the view vector

    mView.z = (float)(mPos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
    mView.x = (float)(mPos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}


void CCamera::Strafe_Camera(float speed,bool YAxis)
{
    tVector3 vVector = mView - mPos;	// Get the view vector

    tVector3 vOrthoVector;              // Orthogonal vector for the view vector

    vOrthoVector.x = -vVector.z;
    vOrthoVector.z =  vVector.x;

    mPos.x  = mPos.x  + vOrthoVector.x * speed;
    mPos.z  = mPos.z  + vOrthoVector.z * speed;
    if (YAxis){
    mView.x = 0;
    mView.z = 0;
    }
    else{
    mView.x = mView.x + vOrthoVector.x * speed;
    mView.z = mView.z + vOrthoVector.z * speed;
    }

}



