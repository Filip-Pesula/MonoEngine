#include "Camera.h"
Camera::Camera():
	mPosition(0, 0, -10),
	mRotation(0, 0, 0),
	mFOVangle(1.f/60.f)
{
}

void Camera::Draw()
{
	for (size_t i = 0; i < ObjRef.size(); i++)
	{
		ObjRef[i]->draw();
	}
}


void Camera::AddObject(Object* object)
{
	ObjRef.push_back(object);
	int CamPosUnif = -1;
	if (CamPosUnif == -1)
	{
		Log("CameraPosition Uniform not Included");
	}

	ObjCameraUniform.push_back(CamPosUnif);
	ObjRefPTR = ObjRef.data();
}

void Camera::SetParams(Vec3f position, Vec3f rotation, float fow)
{
	this->mPosition = position;
	this->mRotation = rotation;
	this->mFOVangle = 1 / fow;
	//this->mFOVangle = fow;
}