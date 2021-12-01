#pragma once
#include <Custom.h>
#include "GR_Object.h"
// CLASS TEMPLATE Camera
class Camera
{
	float mFOVangle;
	std::vector <Object*> ObjRef;
	std::vector<int> ObjCameraUniform;
	Object** ObjRefPTR;
public:
	Vec3f mPosition;
	Vec3f mRotation;
	Camera();
	/**
		Draws Referenced Objects form camera Wiew
		@returns Void
	*/
	void Draw();


	/** 
	*	@brief Adds Object to be drawn on camera. @n
	* 
	* 	Object is Passed my reference.
	*
	*	@param object Object to be rendered by camera
	*	@returns Void
	*/
	void AddObject(Object* object);
	/**
	*	@brief Sets all space parameters of object. @n
	*
	* 	Object is Passed my reference.
	*
	*	@param position sets Position of camera in world space
	*	@param rotation sets Rotation of camera in world space
	*	@param fow sets FOW of camera in angle, if angle is higher than 180, it is set to 180
	*		if angle is lower than 1, it is set to 1 and camera is ortographic
	*	@returns Void
	*/
	void SetParams(Vec3f position, Vec3f rotation, float fow);
	inline Vec3f getPosition()
	{
		return mPosition;
	}
	inline Vec3f getRotation()
	{
		return mRotation;
	}
};