#ifndef CAMERA_H
#define CAMERA_H

#include "SceneObject.h"
#include <assimp/vector3.h>
#include "../Model/Vector3D.h"


class Camera : public SceneObject{
private:
   double aspect;
   double clipPlaneFar;
   double clipPlaneNear;
   double horizontalFOV;
   Vector3D lookAt;
   Vector3D position;
   Vector3D up;
public:

   //Getters
   double getAspect() const;
   double getClipPlaneFar() const;
   double getClipPlaneNear() const;
   double getHorizontalFOV() const;
   Vector3D getLookAt() const;
   Vector3D getPosition() const;
   Vector3D getUp() const;

   //Setters
   void setAspect(double);
   void setClipPlaneFar(double);
   void setClipPlaneNear(double);
   void setHorizontalFOV(double);
   void setLookAt(Vector3D);
   void setPosition(Vector3D);
   void setUp(Vector3D);

   //queste sono da scrivere
   virtual void translate(Vector3D);
   virtual void rotate(double,Vector3D);
   virtual void remove();
   virtual ObjectType getObjectType() const;
   //Constructors
   Camera();
   Camera(QString n,double a, double cpf, double cpn, double hfov, Vector3D la, Vector3D p, Vector3D u);

};

#endif // CAMERA_H
