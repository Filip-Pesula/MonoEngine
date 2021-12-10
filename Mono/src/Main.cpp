#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h> 
#include <Custom.h>
#include <windows.devices.input.h>
#include <Test.h>
#include <MonoStd/monoMath.h>
#include <MonoScpecific/engine/MonoMainWindow.h>
#include <MonoScpecific/testScreen/TestWindow.h>



bool MonoEngineShouldClose = false;

#define DEBUGGL 1

static void GLAPIENTRY OpenGlDebugLog(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam);

#ifndef Debug
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
#else 
int main(void)
#endif // !Debug
{
#ifdef Debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif //Debug


	/* Initialize the library */
	if (!glfwInit())
	{
		Log("ERROR: Cannot Init GLFW");
		return -1;
	}
	/* Create a windowed mode window and its OpenGL context */
	
	//glfwWindowHint(GLFW_SAMPLES, 2);

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	GLFWwindow* backgroundWindow;
	backgroundWindow = glfwCreateWindow(600, 600, "Mono", NULL, NULL);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	if (!backgroundWindow)
	{
		glfwTerminate();
		Log("failed creating backgroundWindow");
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(backgroundWindow);

	if (glewInit() != GLEW_OK)
	{
		Log("ERROR: Cannot Init GLEW");
	}

#ifdef TEST

	Test::testXmlLoader();
	Test::evaluateTests();
	TestUI();
	TestObjLoader();
	return 0;
	//std::vector<std::unique_ptr<Efector>> efectorList;
#endif

	//setup openGlDebugCallback
	glDebugMessageCallback(OpenGlDebugLog,nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);

	
	//setup openGl
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LESS);
	glEnable(GL_BLEND);



	//glfwSwapInterval(0);
	
	glfwSwapInterval(2);

	monoEngine::MonoMainWindow mainWindow;
	test::TestWindow testWindow = test::TestWindow();
	mainWindow.draw();
	testWindow.draw();

	/* Loop until the user closes the window */
	while (!MonoEngineShouldClose)
	{
		//glfwWaitEvents();

		if (mainWindow.WindowShouldClose())
		{
			MonoEngineShouldClose = true;
			continue;
		}
		if (testWindow.WindowShouldClose())
			testWindow.close();
		
		mainWindow.draw();
		testWindow.draw();

		/* Poll for and process events */
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}

#if DEBUGGL
static void GLAPIENTRY OpenGlDebugLog(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		LogError("[Opengl Errror]: " << message);
	case GL_DEBUG_SEVERITY_MEDIUM:
	case GL_DEBUG_SEVERITY_LOW:
	case GL_DEBUG_SEVERITY_NOTIFICATION:
	default:
		break;
	}
}
#else
static void GLAPIENTRY OpenGlDebugLog(
	GLenum source, 
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam) {}
#endif // DEBUG

