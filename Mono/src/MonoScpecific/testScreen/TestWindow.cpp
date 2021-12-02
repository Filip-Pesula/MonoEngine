#include "TestWindow.h"

//#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
//#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

namespace test
{
	TestWindow::TestWindow():
		renderer({ (int)testWindow.mHeight,(int)testWindow.mWidth}),
		text1(
			Unit{ UnitType::px, 11 },
			Vec4f(0, 0, 1, 0),
			"012 456 789\xfd",
			& resourceManager.textTexture,
			Vec2<Unit>(
				Unit{ UnitType::sw,0.0 },
				Unit{ UnitType::sw,0.0 }),
			& slider1),
		slider1(
			{ UnitType::sw, 0.5 },
			{ UnitType::sw, 0.05 },
			Color4(0, 0, 1, 1),
			Vec2<Unit>(
				{ UnitType::sw,0.0 },
				{ UnitType::sw,0.7 }),
			nullptr),
		slider2(
			{ UnitType::sw, 0.5 },
			{ UnitType::sw, 0.05 },
			Color4(0, 0, 1, 1),
			Vec2<Unit>(
				{ UnitType::sw,0.0 },
				{ UnitType::sw,0.1 }),
			&slider1),
		slider3(
		{ UnitType::sw, 0.5 },
		{ UnitType::sw, 0.05 },
		Color4(0, 0, 1, 1),
		Vec2<Unit>(
			{ UnitType::sw,0.0 },
			{ UnitType::sw,0.1 }),
		&slider2),
		btn(
			{ UnitType::sw, 0.2f },
			{ UnitType::sw, 0.2f },
			Color4(0, 1, 0, 0),
			Color4(0, 0, 1, 0.3),
			Vec2<Unit>(
				{ UnitType::sw,0.0 },
				{ UnitType::sw,0.0 }),
			&resourceManager.btnTexture,
			nullptr),
		btn2(
			{ UnitType::sw, 0.1f },
			{ UnitType::sw, 0.1f },
			Vec4f(0, 0, 1, 0.01),
			Vec4f(0, 0, 0, 0.3),
			Vec2<Unit>(
				{ UnitType::sw,0.0 },
				{ UnitType::sw,0.2 }),
			&resourceManager.btnTexture,
			&btn)
	{

		glfwMakeContextCurrent(testWindow.getWindow());
		sphereObject = Object(Vec3f(0.0, 2.0, 15), Vec3f(0, 0, 0), Vec3f(5, 5, 5), Vec3f(0.56, 1, 1), resourceManager.bricksMaterial, resourceManager.sphereObj.fs, nullptr);
		sphereObject.GenMesh();
		cottage = Object(Vec3f(-10.0, 2.0, 0), Vec3f(0, 0, 0), Vec3f(0.1, 0.1, 0.1), Vec3f(0.56, 1, 1), resourceManager.cottageMaterial, resourceManager.CottageObj.fs, nullptr);
		cottage.GenMesh();


		
		Tree1 = Object(Vec3f(10, 0, 0.0), Vec3f(0, 0, 0), Vec3f(0.1, 0.1, 0.1), Vec3f(0.56, 1, 1), resourceManager.treeMaterial, resourceManager.TreeObj.fs, nullptr);
		Tree1.GenMesh();
		Tree2 = Object(Vec3f(0, 0, 2.0), Vec3f(0, 0, 0), Vec3f(0.1, 0.1, 0.1), Vec3f(0.56, 1, 1), resourceManager.treeMaterial, resourceManager.TreeObj.fs, &Tree1);
		Tree2.GenMesh();
		Tree3 = Object(Vec3f(0, 0, 2.0), Vec3f(0, 0, 0), Vec3f(0.1, 0.1, 0.1), Vec3f(0.56, 1, 1), resourceManager.treeMaterial, resourceManager.TreeObj.fs, &Tree2);
		Tree3.GenMesh();
		Tree4 = Object(Vec3f(0, 0, 2.0), Vec3f(0, 0, 0), Vec3f(0.1, 0.1, 0.1), Vec3f(0.56, 1, 1), resourceManager.treeMaterial, resourceManager.TreeObj.fs, &Tree3);
		Tree4.GenMesh();
		RasterPlane = Object(Vec3f(0, -2.5, 1), Vec3f(0, 0, 0), Vec3f(10, 10, 10), Vec3f(0.56, 1, 1), resourceManager.rasterMaterial, resourceManager.RasterPlaneObj.fs, nullptr);
		RasterPlane.GenMesh();

		renderer.AddObject(&Tree1);
		renderer.AddObject(&Tree2);
		renderer.AddObject(&Tree3);
		renderer.AddObject(&Tree4);
		renderer.AddObject(&RasterPlane);
		renderer.AddObject(&sphereObject);
		renderer.AddObject(&cottage);
		renderer.ActiveCamera(&cam1);

		cam1.SetParams(Vec3f(0, 0, -10), Vec3f(0, 0, 0), 1 / 60);
		CameraMove = InputPoll::binAxis<float>(GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S, testWindow.getWindow());


		animate = Animate(&Tree4, Tree4.Position, Tree4.Rotation);
		animate.addPosition(10, Tree4.Position + Vec3f(2, 0, 0));
		animate.addPosition(10, Tree4.Position + Vec3f(0, 0, 0));

		testUIptr = testWindow.getUIptr();
		testUIptr->addElement(&slider1);
		testUIptr->addElement(&slider2);
		testUIptr->addElement(&slider3);

		slider1.mValue = 0.5;
		testUIptr->addElement(&text1);

		testUIptr->addElement(&btn);
		testUIptr->addElement(&btn2);
		btn.addOnclickListner([&]() {
			materialIndex++;
			switch (materialIndex)
			{
			case 0:
			{
				break;
			}
			case 1:
			{
				sphereObject.SetMaterial(resourceManager.bricksMaterial);
				break;
			}
			case 2:
			{
				sphereObject.SetMaterial(resourceManager.bricksNormalMat);
				break;
			}
			default:
				//CubeObject.SetMaterial(wireframe);
				materialIndex = 0;
				break;
			}
			});
		btn2.addOnclickListner([&]()
			{
				if (materialIndex1 == 1)
				{
					materialIndex1 = 0;
					RasterPlane.SetMaterial(resourceManager.rasterMaterial);
				}
				else
				{
					materialIndex1 = 1;
					RasterPlane.SetMaterial(resourceManager.wireframe);
				}
			});
	}

	void TestWindow::draw()
	{
		glfwMakeContextCurrent(testWindow.getWindow());
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glClearDepth(1.0f);
		glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		std::string valueText = std::to_string(slider1.mValue);
		text1.setText(valueText);

		animate.calcualte();

		renderer.Draw();


		testUIptr->getUI();
		testUIptr->Draw();
		/*
		int width, height;
		glfwGetWindowSize(testWindow.getWindow(), &width, &height);
		glViewport(width / 2, height / 2, width /2, height/2);
		renderer.Draw();
		*/
		renderer.setSize(testWindow.getSize());
		moveCamera();
		moveObject();

		testWindow.swapBuffers();
	}

	void TestWindow::moveCamera()
	{
		CameraMove.get();

		sppedScale = 1;
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_LEFT_SHIFT))
		{
			sppedScale = 10;
		}
		Vec2<float> cameraAngle;
		cameraAngle.x = (float)sin(mono::degToRad(cam1.mRotation.y));
		cameraAngle.y = (float)cos(mono::degToRad(cam1.mRotation.y));
		float mag = cameraAngle.magnitude();
		std::string valueText = std::to_string(slider1.mValue);
		text1.setText(valueText);

		cam1.mPosition.z -= sppedScale * CameraMove.Axes.y * cameraAngle.y * 0.01f;
		cam1.mPosition.x -= sppedScale * CameraMove.Axes.y * cameraAngle.x * 0.01f;

		cam1.mPosition.x += sppedScale * CameraMove.Axes.x * cameraAngle.y * 0.01f;
		cam1.mPosition.z += sppedScale * CameraMove.Axes.x * (-cameraAngle.x) * 0.01f;

		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_SPACE))
		{
			cam1.mPosition.y += 0.01f * sppedScale;
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_LEFT_CONTROL))
		{
			cam1.mPosition.y -= 0.01f * sppedScale;
		}


		glfwGetCursorPos(testWindow.getWindow(), &mousePos.x, &mousePos.y);
		Vec2f Diference = mouseMem - mousePos;
		if (glfwGetMouseButton(testWindow.getWindow(), GLFW_MOUSE_BUTTON_RIGHT))
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
	void TestWindow::moveObject()
	{

		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_V))
		{
			sphereObject.Scale.x = sphereObject.Scale.x * 1.01f;
			sphereObject.Scale.y = sphereObject.Scale.y * 1.01f;
			sphereObject.Scale.z = sphereObject.Scale.z * 1.01f;
		}
		if (glfwGetKey(testWindow.getWindow(), GLFW_KEY_B))
		{
			sphereObject.Scale.x = sphereObject.Scale.x * 0.99f;
			sphereObject.Scale.y = sphereObject.Scale.y * 0.99f;
			sphereObject.Scale.z = sphereObject.Scale.z * 0.99f;
		}

		sphereObject.Rotation.y = slider1.mValue * 360;
		sphereObject.Rotation.x = slider2.mValue * 360;
		sphereObject.Rotation.z = slider3.mValue * 360;
	}
	bool TestWindow::WindowShouldClose()
	{
		return testWindow.WindowShouldClose();
	}
	void TestWindow::close()
	{
		testWindow.close();
	}
}
