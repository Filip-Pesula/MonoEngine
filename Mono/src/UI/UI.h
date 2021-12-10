#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Texture.h>
#include <Custom.h>
#include "UIShaderString.h"
#include "Elements/UiElements.h"
#include "UIshader.h"
#include "UIenums.h"
#include "BeGL/BeGL_FrameBuffer.h"
#include "Cursor.h"
#include <array>

namespace UI
{
	class UI
	{
	protected:
		int maxDrawIndex = -1;
		unsigned int frameBuffer;
		unsigned int renderBuffer;
		std::vector<Texture> TextureList;
		Texture SliderTexture;
		std::vector<std::string> TextureNameList;
		UIShader ShaderUIShader = UIShader(UIShaders::VShaderString, UIShaders::FShaderString);
		MouseState LMBState = MouseState::FREE;

		GLFWcursor* hScaleCursor;
		GLFWcursor* vScaleCursor;
		GLFWcursor* iBeamCursor;
		GLFWcursor* handCursor;
		GLFWcursor* pointCursor;

		GLFWcursor* activeCursor;

		Cursor cursor;

		std::vector<UIelement*>  elementList;

		std::vector<std::pair<std::array<int,5>,std::function<void(void)>>> shortuchCallbacks;

		float* tiledVertex;
		unsigned int* tiledIndex;
		unsigned int eTiledVertex;
		unsigned int eTiledIndex;

	public:
		~UI();
		Vec2d MousePos;
		Vec2d MousePosNormal;
		GLFWwindow* eWindow;
		const std::string VshaderCode = UIShaders::VShaderString;
		const std::string FshaderCode = UIShaders::FShaderString;

		void generateEdgeVertex(float** vertexArray, unsigned int** indexArray, float textureEdge);
		void generateQuadVertex(float* vertexArray);

		void CreateShader(UIShader& uiShader);
		static int CompileShader(const std::string& source, unsigned int Vertype);

		void genStaticBuffers(unsigned int &vertexBufferRef, unsigned int &indexBufferRef, float* vertexBuffer, int vertexBufferSize, unsigned int* indexBuffer, int indexBufferSize);
		virtual void InitUI(GLFWwindow* window);
		void addElement(UIelement* elementPtr);
		void addGlobaShortCutListener(std::array<int,5> keys, std::function<void(void)> callback);
		int Add_Texture(std::string TextureRef, std::string  TextureName);
		int Add_TextTexture(std::string TextureRef, std::string  TextureName);
		
		void getUI();
		void BindShaderBuffer();
		
		virtual void Draw();
	};

}