#pragma once
#include <Custom.h>
#include "Camera.h"
#include "GR_Object.h"
#include <resourceManagment/ShaderLoader.h>
#include <BeGL/BeGL.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Renderer
{
	std::vector <ShaderScript*> ShaderCollection;
	std::vector <Object*> ObjRef;
	std::vector <Camera*> CamRef;
	Vec3f screenScale;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	Camera* activeCamera;
public:
	Renderer(Vec2i screenSize)
	{
		screenScale.x = (screenSize.y) / (screenSize.x);
		screenScale.y = 1;
		screenScale.z = 1;
	}

	void setSize(Vec2i screenSize);

	void AddObject(Object* object)
	{
		bool ShaderNotIncluded = true;
		for (size_t i = 0; i < ObjRef.size(); i++)
		{

			if (&object->material.shaderScript == &ObjRef[i]->material.shaderScript)
			{
				ShaderNotIncluded = false;
			}
		}
		if (ShaderNotIncluded)
		{
			ShaderCollection.push_back(&object->material.shaderScript);
		}
		ObjRef.push_back(object);
	}

	void Draw()
	{
		if (activeCamera == nullptr)
		{
			Log("No Active Camera!!!");
			return;
		}
		glm::vec3 cameraVertex = glm::vec3(0.0, 0.0, -1.0);

		glm::vec3 lRotationX = glm::rotate(cameraVertex, activeCamera->mRotation.x, glm::vec3(1, 0, 0));
		glm::vec3 lRotationY = glm::rotate(lRotationX, activeCamera->mRotation.y, glm::vec3(0, 1, 0));
		glm::vec3 lRotationZ = glm::rotate(lRotationY, activeCamera->mRotation.z, glm::vec3(0, 0, 1));
		cameraVertex = lRotationZ;
		glm::vec3 cameraPosition = glm::vec3(activeCamera->mPosition.x, activeCamera->mPosition.y, activeCamera->mPosition.z);
		//ViewMatrix = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0,0,1), glm::vec3(0.0f, 1.0f, 0.0f));
		
		ProjectionMatrix = glm::perspective(glm::radians(60.0f),16.0f/9.0f,0.1f,2000.0f);
		//ProjectionMatrix = glm::ortho(-10,10,-10,10);
		ShaderScript activeShader;
		
		for (size_t i = 0; i < ShaderCollection.size(); i++)
		{
			activeShader = *ShaderCollection[i];
			glUseProgram(activeShader.shaderID);
			BeGL::setUninformMat4f(activeShader.rUniforms.uViewMatrix, ViewMatrix);
			BeGL::setUninformMat4f(activeShader.rUniforms.uProjectionMatrix, ProjectionMatrix);
			BeGL::setUniform3f(activeShader.rUniforms.uCamPosition, activeCamera->getPosition());
			BeGL::setUniform3f(activeShader.rUniforms.uCamRotation, activeCamera->getRotation());
			BeGL::setUniform3f(activeShader.rUniforms.uScreenScale, screenScale);
		}
		for (size_t i = 0; i < ObjRef.size(); i++)
		{
			activeShader = ObjRef[i]->material.shaderScript;

			ObjRef[i]->setViewMatrix(ViewMatrix);
			ObjRef[i]->draw();
		}
	}

	void ActiveCamera(Camera* camera)
	{
		activeCamera = camera;
	}

};