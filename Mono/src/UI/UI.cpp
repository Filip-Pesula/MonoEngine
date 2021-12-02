#include "UI.h"
#include "UI.h"
namespace UI
{
	void UI::generateEdgeVertex(float** vertexArray, unsigned int** indexArray, float textureEdge)
	{
		*vertexArray = new float[16 * (2 + 2)];
		float* NvertexArray = *vertexArray;
		//inner square
		NvertexArray[0] = -0.2f; NvertexArray[1] = 0.2f; NvertexArray[2] = 0.4f; NvertexArray[3] = 0.6f; //0
		NvertexArray[4] = 0.2f; NvertexArray[5] = 0.2f; NvertexArray[6] = 0.6f; NvertexArray[7] = 0.6f; //1
		NvertexArray[8] = 0.2f; NvertexArray[9] = -0.2f; NvertexArray[10] = 0.6f; NvertexArray[11] = 0.4f; //2
		NvertexArray[12] = -0.2f; NvertexArray[13] = -0.2f; NvertexArray[14] = 0.4f; NvertexArray[15] = 0.4f; //3
		//outer edges
		NvertexArray[16] = -1.0f; NvertexArray[17] = 1.0f; NvertexArray[18] = 0.0f; NvertexArray[19] = 1.0f; //4
		NvertexArray[20] = -0.2f; NvertexArray[21] = 1.0f; NvertexArray[22] = 0.4f; NvertexArray[23] = 1.0f; //5
		NvertexArray[24] = 0.2f; NvertexArray[25] = 1.0f; NvertexArray[26] = 0.6f; NvertexArray[27] = 1.0f; //6

		NvertexArray[28] = 1.0f; NvertexArray[29] = 1.0f; NvertexArray[30] = 1.0f; NvertexArray[31] = 1.0f; //7
		NvertexArray[32] = 1.0f; NvertexArray[33] = 0.2f; NvertexArray[34] = 1.0f; NvertexArray[35] = 0.6f; //8
		NvertexArray[36] = 1.0f; NvertexArray[37] = -0.2f; NvertexArray[38] = 1.0f; NvertexArray[39] = 0.4f; //9

		NvertexArray[40] = 1.0f; NvertexArray[41] = -1.0f; NvertexArray[42] = 1.0f; NvertexArray[43] = 0.0f; //10
		NvertexArray[44] = 0.2f; NvertexArray[45] = -1.0f; NvertexArray[46] = 0.6f; NvertexArray[47] = 0.0f; //11
		NvertexArray[48] = -0.2f; NvertexArray[49] = -1.0f; NvertexArray[50] = 0.4f; NvertexArray[51] = 0.0f; //12

		NvertexArray[52] = -1.0f; NvertexArray[53] = -1.0f; NvertexArray[54] = 0.0f; NvertexArray[55] = 0.0f; //13
		NvertexArray[56] = -1.0f; NvertexArray[57] = -0.2f; NvertexArray[58] = 0.0f; NvertexArray[59] = 0.4f; //14
		NvertexArray[60] = -1.0f; NvertexArray[61] = 0.2f; NvertexArray[62] = 0.0f; NvertexArray[63] = 0.6f; //15

		*indexArray = new unsigned int[54];
		unsigned int* NindexArray = *indexArray;
		//middle
		NindexArray[0] = 0; NindexArray[1] = 1; NindexArray[2] = 2;
		NindexArray[3] = 3; NindexArray[4] = 0; NindexArray[5] = 2;
		//top left
		NindexArray[6] = 0; NindexArray[7] = 15; NindexArray[8] = 4;
		NindexArray[9] = 4; NindexArray[10] = 5; NindexArray[11] = 0;
		//top
		NindexArray[12] = 0; NindexArray[13] = 5; NindexArray[14] = 6;
		NindexArray[15] = 6; NindexArray[16] = 1; NindexArray[17] = 0;
		//top right
		NindexArray[18] = 1; NindexArray[19] = 6; NindexArray[20] = 7;
		NindexArray[21] = 7; NindexArray[22] = 8; NindexArray[23] = 1;
		//right
		NindexArray[24] = 1; NindexArray[25] = 8; NindexArray[26] = 9;
		NindexArray[27] = 9; NindexArray[28] = 2; NindexArray[29] = 1;
		//bot right
		NindexArray[30] = 2; NindexArray[31] = 9; NindexArray[32] = 10;
		NindexArray[33] = 10; NindexArray[34] = 11; NindexArray[35] = 2;
		//bot
		NindexArray[36] = 2; NindexArray[37] = 11; NindexArray[38] = 12;
		NindexArray[39] = 12; NindexArray[40] = 3; NindexArray[41] = 2;
		//bot left
		NindexArray[42] = 3; NindexArray[43] = 12; NindexArray[44] = 13;
		NindexArray[45] = 13; NindexArray[46] = 14; NindexArray[47] = 3;
		//left
		NindexArray[48] = 3; NindexArray[49] = 14; NindexArray[50] = 15;
		NindexArray[51] = 15; NindexArray[52] = 0; NindexArray[53] = 3;
	}
	void UI::generateQuadVertex(float* vertexArray)
	{
		vertexArray = new float[4 * (2 + 2)];
	}
	UI::~UI()
	{
		glDeleteBuffers(1, &eTiledVertex);
		glDeleteBuffers(1, &eTiledIndex);
		delete[] tiledVertex;
		delete[] tiledIndex;
	}
	void UI::CreateShader(UIShader& uiShader)
	{
		uiShader.shaderID = glCreateProgram();
		int vertSh = CompileShader(uiShader.VertShaderTxt, GL_VERTEX_SHADER);
		int fragSh = CompileShader(uiShader.FragShaderTxt, GL_FRAGMENT_SHADER);
		glAttachShader(uiShader.shaderID, vertSh);
		glAttachShader(uiShader.shaderID, fragSh);
		glLinkProgram(uiShader.shaderID);
		glValidateProgram(uiShader.shaderID);

		glDeleteProgram(vertSh);
		glDeleteProgram(fragSh);

		uiShader.rUniforms.uScale = glGetUniformLocation(uiShader.shaderID, "uScale");
		uiShader.rUniforms.uColor = glGetUniformLocation(uiShader.shaderID, "uColor");
		uiShader.rUniforms.uPosition = glGetUniformLocation(uiShader.shaderID, "uPosition");
		uiShader.rUniforms.uRotation = glGetUniformLocation(uiShader.shaderID, "uRotation");
		uiShader.rUniforms.uTexture = glGetUniformLocation(uiShader.shaderID, "uTexture");
		uiShader.rUniforms.uScreenScale = glGetUniformLocation(uiShader.shaderID, "uScreenScale");
		uiShader.rUniforms.uDrawmode = glGetUniformLocation(uiShader.shaderID, "uDrawMode");
		uiShader.rUniforms.uBorder = glGetUniformLocation(uiShader.shaderID, "uBorder");
	}
	int UI::CompileShader(const std::string& source, unsigned int Vertype)
	{
		unsigned int id = glCreateShader(Vertype);
		const char* scr = source.c_str();
		glShaderSource(id, 1, &scr, nullptr);
		glCompileShader(id);

		//error
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int lenght;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
			char* message = (char*)alloca(lenght * sizeof(char));
			glGetShaderInfoLog(id, lenght, &lenght, message);
			std::cout << message << std::endl;
		}
		return id;
	}
	void UI::genStaticBuffers(unsigned int &vertexBufferRef, unsigned int &indexBufferRef, float* vertexBuffer, int vertexBufferSize, unsigned int* indexBuffer, int indexBufferSize)
	{
		glGenBuffers(1, &vertexBufferRef);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferRef);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexBufferSize, vertexBuffer, GL_STATIC_DRAW);
		glGenBuffers(1, &indexBufferRef);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferRef);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexBufferSize, indexBuffer, GL_STATIC_DRAW);
	}
	void UI::InitUI(GLFWwindow* window)
	{
		hScaleCursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		vScaleCursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		pointCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		iBeamCursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		activeCursor = pointCursor;
		cursor.activeCursor = pointCursor;
		glfwSetCursor(window, activeCursor);
		eWindow = window;
		CreateShader(ShaderUIShader);
		SliderTexture = Texture("Textures\\slider32.png",Texture::TextureType::uI_texture);
		generateEdgeVertex(&tiledVertex, &tiledIndex, 0);
		genStaticBuffers(eTiledVertex, eTiledIndex, tiledVertex, 64, tiledIndex, 54);
	}
	void UI::addElement(UIelement* elementPtr)
	{
		elementList.push_back(elementPtr);
		maxDrawIndex++;
		elementList[elementList.size() - 1]->drawIndex = maxDrawIndex;
	}
	int UI::Add_Texture(std::string TextureRef, std::string  TextureName)
	{
		TextureList.push_back(Texture(TextureRef, Texture::TextureType::uI_texture));
		TextureNameList.push_back(TextureName);
		return TextureList.size() - 1;
	}
	int UI::Add_TextTexture(std::string TextureRef, std::string  TextureName)
	{
		TextureList.push_back(Texture(TextureRef, Texture::TextureType::text));
		TextureNameList.push_back(TextureName);
		return TextureList.size() - 1;
	}
	void UI::getUI()
	{

		if ((glfwGetMouseButton(eWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) && (LMBState == MouseState::RELEAS))
		{
			LMBState = MouseState::FREE;
		}
		if ((glfwGetMouseButton(eWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) && ((LMBState == MouseState::HOLD) || (LMBState == MouseState::PRESS)))
		{
			LMBState = MouseState::RELEAS;
		}
		if ((glfwGetMouseButton(eWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && (LMBState == MouseState::PRESS))
		{
			LMBState = MouseState::HOLD;
		}
		if ((glfwGetMouseButton(eWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && (LMBState == MouseState::FREE))
		{
			LMBState = MouseState::PRESS;
		}
		
		glfwGetCursorPos(eWindow, &MousePos.x, &MousePos.y);
		int width, height;
		glfwGetWindowSize(eWindow, &width, &height);
		MousePosNormal.x = MousePos.x / width;
		MousePosNormal.y = MousePos.y / height;
		glViewport(0, 0, width, height);
		activeCursor = pointCursor;
		cursor.LMBState = LMBState;
		cursor.position = MousePosNormal;
		cursor.iPosition = MousePos;
		cursor.activeCursor = activeCursor;

		for (int i = elementList.size()-1; i >=0; i--)
		{
			if (elementList[i]->MouseRay(cursor))
			{
				activeCursor = handCursor;
			}
		}
	}
	void UI::BindShaderBuffer()
	{
		glUseProgram(ShaderUIShader.shaderID);
		glBindBuffer(GL_ARRAY_BUFFER, eTiledVertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eTiledIndex);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

	}
	void UI::Draw()
	{
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		BindShaderBuffer();

		int width, height;
		glfwGetWindowSize(eWindow, &width, &height);
		glViewport(0,0, width , height );
		/*
		if (glfwGetWindowAttrib(eWindow, GLFW_FOCUSED))
		{
			glfwSetCursor(eWindow, activeCursor);
		}
		*/
		glfwSetCursor(eWindow, activeCursor);
		for (int j = 0; j <= maxDrawIndex; j++)
		{
			/*
			for (int i = 0; i < ButtonList.size(); i++)
			{
				if (ButtonList[i]->drawIndex != j)continue;
				BindShaderBuffer();
				ButtonList[i]->Resize({ width ,height });
				ButtonList[i]->Draw(ShaderUIShader, TextureList);
			}
			for (int i = 0; i < TextList.size(); i++)
			{
				if (TextList[i]->drawIndex != j)continue;
				TextList[i]->Resize({ width ,height });
				TextList[i]->Draw(ShaderUIShader, TextureList);
			}
			for (int i = 0; i < ContainerList.size(); i++)
			{
				if (ContainerList[i]->drawIndex != j)continue;
				BindShaderBuffer();
				ContainerList[i]->Resize({ width ,height });
				ContainerList[i]->Draw(ShaderUIShader);
			}
			for (int i = 0; i < GrabberList.size(); i++)
			{
				if (GrabberList[i]->drawIndex != j)continue;
				BindShaderBuffer();
				GrabberList[i]->Resize({ width ,height });
				GrabberList[i]->Draw(ShaderUIShader);
			}
			*/
			for (int i = 0; i < elementList.size(); i++)
			{
				if (elementList[i]->drawIndex != j)continue;
				BindShaderBuffer();
				elementList[i]->Resize({ width ,height });
				elementList[i]->Draw(ShaderUIShader);
			}
		}
		
	}
}