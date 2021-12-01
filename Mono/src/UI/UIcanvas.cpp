#include "UIcanvas.h"
namespace UI
{
	void UIcanvas::InitUI(GLFWwindow* window, int width, int heihgt, Vec4f backgroundColor)
	{
		hScaleCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		pointCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);

		eWindow = window;
		CreateShader(ShaderUIShader);
		SliderTexture = Texture("G:\\Programming\\c++\\MonoEngine\\Mono\\Textures\\slider32.png", Texture::TextureType::uI_texture);
		generateEdgeVertex(&tiledVertex, &tiledIndex, 0);
		genStaticBuffers(eTiledVertex, eTiledIndex, tiledVertex, 64, tiledIndex, 54);
		frameBuffer = BeGL::GlFrameBuffer(width, heihgt);
		this->canvasTexture = &frameBuffer.FrameBufferColorTexture;
		mBackgroundColor = backgroundColor;
	}
	void UIcanvas::Draw()
	{
		//glfwSetCursor(Window, hScaleCurousor);
		frameBuffer.bind();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		BindShaderBuffer();

		frameBuffer.unbind();
	}
}