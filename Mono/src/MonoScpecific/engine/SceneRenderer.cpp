#include "SceneRenderer.h"
#include <MonoStd/monoMath.h>
#include <BeGL/BeGL.h>
#include <src/MonoScpecific/engine/Efectors/MoveEfector.h>
namespace monoEngine
{
	void SceneRenderer::moveCamera()
	{
		CameraMove.get();

		float sppedScale = 1;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		{
			sppedScale = 10;
		}
		Vec2<float> cameraAngle;
		cameraAngle.x = (float)sin(mono::degToRad(cam1.mRotation.y));
		cameraAngle.y = (float)cos(mono::degToRad(cam1.mRotation.y));
		float mag = cameraAngle.magnitude();

		cam1.mPosition.z -= sppedScale * CameraMove.Axes.y * cameraAngle.y * 0.01f;
		cam1.mPosition.x -= sppedScale * CameraMove.Axes.y * cameraAngle.x * 0.01f;

		cam1.mPosition.x += sppedScale * CameraMove.Axes.x * cameraAngle.y * 0.01f;
		cam1.mPosition.z += sppedScale * CameraMove.Axes.x * (-cameraAngle.x) * 0.01f;

		if (glfwGetKey(window, GLFW_KEY_SPACE))
		{
			cam1.mPosition.y += 0.01f * sppedScale;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
		{
			cam1.mPosition.y -= 0.01f * sppedScale;
		}


		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
		Vec2f Diference = mouseMem - mousePos;
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			cam1.mRotation.x += Diference.y / 10;
			cam1.mRotation.y += Diference.x / 10;
		}
		if (cam1.mRotation.y > 45)
		{
			//cam1.mRotation.y = -45;
		}
		else
		{
			//cam1.mRotation.y += 0.1;
		}
		mouseMem = mousePos;


	}
	SceneRenderer::SceneRenderer(ResourceManager& resourceManager, GLFWwindow* window, RenderElement* renderFrame) :
		renderer({ 100 , 100 }),
		resourceManager(resourceManager),
		window(window),
		renderFrame(renderFrame),
		CubeObject(Vec3f(0.f, 2.f, 15.f), Vec3f(0.f, 0.f, 0.f), Vec3f(5.f, 5.f, 5.f), Vec3f(0.56f, 1.f, 1.f), resourceManager.bricksNormalMat, resourceManager.CottageObj.fs, nullptr),
		Tree1(Vec3f(10.f, 0.f, 0.f), Vec3f(0.f, 0.f, 0.f), Vec3f(0.1f, 0.1f, 0.1f), Vec3f(0.56f, 1.f, 1.f), resourceManager.treeMaterial, resourceManager.TreeObj.fs, nullptr),
		Tree2(Vec3f(0.f, 0.f, 2.f), Vec3f(0.f, 0.f, 0.f), Vec3f(0.1f, 0.1f, 0.1f), Vec3f(0.56f, 1.f, 1.f), resourceManager.treeMaterial, resourceManager.TreeObj.fs, &Tree1),
		Tree3(Vec3f(0.f, 0.f, 2.f), Vec3f(0.f, 0.f, 0.f), Vec3f(0.1f, 0.1f, 0.1f), Vec3f(0.56f, 1.f, 1.f), resourceManager.treeMaterial, resourceManager.TreeObj.fs, &Tree2),
		Tree4(Vec3f(0.f, 0.f, 2.f), Vec3f(0.f, 0.f, 0.f), Vec3f(0.1f, 0.1f, 0.1f), Vec3f(0.56f, 1.f, 1.f), resourceManager.treeMaterial, resourceManager.TreeObj.fs, &Tree3),
		RasterPlane(Vec3f(0.f, -2.5f, 1.f), Vec3f(0.f, 0.f, 0.f), Vec3f(10.f, 10.f, 10.f), Vec3f(0.56f, 1.f, 1.f), resourceManager.rasterMaterial, resourceManager.RasterPlaneObj.fs, nullptr),
		CameraMove(GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S, window)
	{
		CubeObject.GenMesh();
		Tree1.GenMesh();
		Tree2.GenMesh();
		Tree3.GenMesh();
		Tree4.GenMesh();
		RasterPlane.GenMesh();

		renderer.AddObject(&Tree1);
		renderer.AddObject(&Tree2);
		renderer.AddObject(&Tree3);
		renderer.AddObject(&Tree4);
		renderer.AddObject(&RasterPlane);
		renderer.AddObject(&CubeObject);
		renderer.ActiveCamera(&cam1);

		cam1.SetParams(Vec3f(0, 0, -10), Vec3f(0, 0, 0), 1 / 60);

	}
	void SceneRenderer::SetAcvtiveScene(Scene* activeScene)
	{
		this->activeScene = activeScene;
		if (activeScene != nullptr) {
			std::for_each(activeScene->objects.begin(), activeScene->objects.end(),
				[&](std::unique_ptr<SceneObject> &obj) {
					Vec3f objectPos = std::any_cast<Vec3f>(obj->efectorList[0]->getProperty("position"));
					Vec3f objectRot = std::any_cast<Vec3f>(obj->efectorList[0]->getProperty("rotation"));
					objects.push_back(std::move(std::make_unique<Object>(objectPos, objectRot, Vec3f(1.f, 1.f, 1.f), Vec3f(0.56, 1, 1), resourceManager.crossMat, resourceManager.cross,nullptr)));
					objects[objects.size() - 1]->GenMesh();
					renderer.AddObject((objects[objects.size()-1]).get());
				});
		}

	}
	void SceneRenderer::draw()
	{
		std::for_each(activeScene->objects.begin(), activeScene->objects.end(),
			[&](std::unique_ptr<SceneObject>& obj) {
				std::for_each(obj->efectorList.begin(), obj->efectorList.end(), 
					[](std::unique_ptr <Efector>& ef) {
						ef->execute();
					});
			});

		if (activeScene != nullptr) {
			
			for (size_t i = 0; i < activeScene->objects.size(); i++)
			{
				std::unique_ptr<SceneObject>& obj = activeScene->objects[i];
				Vec3f objectPos = std::any_cast<Vec3f>(obj->efectorList[0]->getProperty("position"));
				Vec3f objectRot = std::any_cast<Vec3f>(obj->efectorList[0]->getProperty("rotation"));
				objects[i]->Position = objectPos;
				objects[i]->Rotation = objectRot;
			}
			
		}
		glfwMakeContextCurrent(window);
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		Vec2f framePosition = renderFrame->getG_Position();
		glViewport(
			(GLint)((framePosition.x + 1.0f) / 2.0f * (float)screenWidth - (float)getFrameWidth(screenWidth)/2.0f),
			(GLint)((framePosition.y + 1.0f) / 2.0f * (float)screenHeight - (float)getFrameHeight(screenHeight)/2.0f - 2.0f),
			getFrameWidth(screenWidth),
			getFrameHeight(screenHeight)+2);
		/*
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glClearDepth(1.0f);
		glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		*/
		
		renderer.Draw();
		renderer.setSize({ getFrameWidth(screenWidth) , getFrameHeight(screenHeight) });
		moveCamera();
	}
	int SceneRenderer::getFrameWidth(int screenWidth)
	{
		return (int)(renderFrame->getG_Width() * screenWidth);
	}
	int SceneRenderer::getFrameHeight(int screenHeight)
	{
		return (int)(renderFrame->getG_Height() * screenHeight);
	}
}