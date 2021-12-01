#pragma once
#include <Custom.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <GL/glew.h>
namespace shader
{
	enum LayoutVertex
	{
		VecPoint, //3 flat vertex 
		VecNormal, //3 flat vertex
		VecTangent, //3 flat vertex
		VecBitangent, //3 flat vertex
		VecTexture, //2 flat vertex
		ColorRGB, //3 flat vertex
		ColorRGBA, //4 flat vertex
		empty
	};

};
struct ShaderScript
{
	struct RUniforms
	{
		int uPosition; //uPosition
		int uRotation; //uRotation
		int uScale;
		int uCamPosition;
		int uCamRotation;
		int uFOW;
		int uScreenScale;
		int uModelMatrix;
		int uViewMatrix;
		int uProjectionMatrix;
	};
	std::string shaderName;
	int shaderID;
	RUniforms rUniforms;

};

class shader_file	//for linking shader from file
{
	bool compile_error;
	public: 
		unsigned int program;
		unsigned int Cprogram;
		unsigned int Vshader;
		unsigned int Fshader;
		unsigned int Cshader;
		std::string* VshaderCode;
		std::string* FshaderCode;
		std::string* CshaderCode;

		ShaderScript shader;


	void File_CompileShader(const std::string* shaderCode, unsigned int& shader, unsigned int shade_type)
	{
		std::string m = *shaderCode;
		shader = glCreateShader(shade_type);
		const char* sourceCode = m.c_str();
		glShaderSource(shader, 1, &sourceCode, NULL);
		glCompileShader(shader);
		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lenght);
			char* message = new char[lenght];
			glGetShaderInfoLog(shader, lenght, &lenght, message);
			std::cout << message << std::endl;
			std::cout << *shaderCode << std::endl;

		}
		glAttachShader(program, shader);

	}
	void Compile_Compute_shader()
	{
		if (read_shader(CshaderCode, "Shaders\\Compute.comp"));
		else return;
		std::cout << *CshaderCode << std::endl;

		std::string m = *CshaderCode;
		Cprogram = glCreateProgram();
		Cshader = glCreateShader(GL_COMPUTE_SHADER);
		const char* sourceCode = m.c_str();
		glShaderSource(Cshader, 1, &sourceCode, NULL);
		glCompileShader(Cshader);
		int result;
		glGetShaderiv(Cshader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(Cshader, GL_INFO_LOG_LENGTH, &lenght);
			char* message = new char[lenght];
			glGetShaderInfoLog(Cshader, lenght, &lenght, message);
			std::cout << message << std::endl;
		}
		glAttachShader(Cprogram, Cshader);
		delete CshaderCode;

		glLinkProgram(Cprogram);
		glValidateProgram(Cprogram);
		glDeleteShader(Cshader);
	}

	public: void File_CreateShader(std::string fileName)
	{
		program = glCreateProgram();
		if (read_shader(VshaderCode, "Shaders\\" + fileName + "\\Vshader.vert"));
		else return;
		//std::cout << *VshaderCode << std::endl;
		File_CompileShader(VshaderCode, Vshader, GL_VERTEX_SHADER);
		delete VshaderCode;

		if (read_shader(FshaderCode, "Shaders\\" + fileName + "\\Fshader.frag"));
		else return;
		//std::cout << *FshaderCode << std::endl;
		File_CompileShader(FshaderCode, Fshader, GL_FRAGMENT_SHADER);
		delete FshaderCode;
		glAttachShader(program, Vshader);
		glAttachShader(program, Fshader);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteShader(Vshader);
		glDeleteShader(Fshader);

		shader.shaderName =  fileName;
		shader.shaderID = program;
#pragma region GetUniforms
			shader.rUniforms.uPosition = glGetUniformLocation(program, "uPosition");
			if (shader.rUniforms.uPosition == -1)
			{
				Log("Cannot find Uniform: uPosition");
			}
			shader.rUniforms.uRotation = glGetUniformLocation(program, "uRotation");
			if (shader.rUniforms.uRotation == -1)
			{
				Log("Cannot find Uniform: uRotation");
			}
			shader.rUniforms.uScale = glGetUniformLocation(program, "uScale");
			if (shader.rUniforms.uScale == -1)
			{
				Log("Cannot find Uniform: uScale");
			}

			shader.rUniforms.uCamPosition = glGetUniformLocation(program, "uCamPosition");
			if (shader.rUniforms.uCamPosition == -1)
			{
				Log("Cannot find Uniform: uCamPosition");
			}
			shader.rUniforms.uCamRotation = glGetUniformLocation(program, "uCamRotation");
			if (shader.rUniforms.uCamRotation == -1)
			{
				Log("Cannot find Uniform: uCamRotation");
			}
			shader.rUniforms.uFOW = glGetUniformLocation(program, "uFOW");
			if (shader.rUniforms.uFOW == -1)
			{
				Log("Cannot find Uniform: FOW");
			}
			shader.rUniforms.uScreenScale = glGetUniformLocation(program, "uScreenScale");
			if (shader.rUniforms.uScreenScale == -1)
			{
				Log("Cannot find Uniform: uScreenScale");
			}
			shader.rUniforms.uModelMatrix = glGetUniformLocation(program, "uModelMatrix");
			if (shader.rUniforms.uModelMatrix == -1)
			{
				Log("Cannot find Uniform: uModelMatrix");
			}
			shader.rUniforms.uViewMatrix = glGetUniformLocation(program, "uViewMatrix");
			if (shader.rUniforms.uViewMatrix == -1)
			{
				Log("Cannot find Uniform: uViewMatrix");
			}
			shader.rUniforms.uProjectionMatrix = glGetUniformLocation(program, "uProjectionMatrix");
			if (shader.rUniforms.uProjectionMatrix == -1)
			{
				Log("Cannot find Uniform: uProjectionMatrix");
			}
#pragma endregion GetUniforms
	}

	public: bool read_shader(std::string* &shadertxt, std::string fileadr)
	{
		std::ifstream file(fileadr);
		if (file.is_open())
		{
			std::string line;
			std::stringstream data;

			while (file.good())
			{
				getline(file, line);
				data << line << "\n";
				
			}

			if (file)
			{
				std::cout << "all characters read successfully." << std::endl;
				shadertxt = new std::string;
				*shadertxt = data.str();
				return(1);
			}
			else
			{
				std::cout << "read error:" << std::endl;
				delete VshaderCode;
				return(0);
			}

		}
		else
		{
			std::cout << "nelze nalest:  " << fileadr << std::endl;
			return(0);
		}

	}
};

class shader_static
{
public: unsigned int program;
	  unsigned int Cprogram;
	  unsigned int Vshader;
	  unsigned int Fshader;
	  unsigned int Cshader;

	  const std::string VshaderCode =
		  "#version 430\n"
		  "\n"
		  "#define M_PI 3.1415926535897932384626433832795\n"
		  "layout(location = 0) in vec4 point_array;\n"
		  "layout(location = 1) in vec4 color_array;\n"
		  "uniform vec4 position;\n"
		  "uniform vec3 rotation;\n"
		  "uniform vec3 scale;\n"
		  "vec4 resized;\n"
		  "out vec4 pos;\n"
		  "out vec2 TexPos;\n"
		  "mat4 rotationMatrix(vec3 axis, float angle)\n" 
		  "{ \n"
		  "	axis = normalize(axis);\n"
		  " float s = sin(angle);\n"
		  " float c = cos(angle);\n"
		  " float oc = 1.0 - c;\n"

		  "  return mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,\n"
		  "	 oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,\n"
		  "  oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,\n"
		  "  0.0, 0.0, 0.0, 1.0);\n"
		  "}\n"
		  "vec3 rotate(vec3 v, vec3 axis, float angle) {\n"
		  "	  mat4 m = rotationMatrix(axis, angle);\n"
		  "	  return (m * vec4(v, 1.0)).xyz;\n"
		  "}\n"
		  "\n"
		  "void main()\n"
		  "{\n"
		  "	resized.x = point_array.x * scale.x;\n"
		  "	resized.y = point_array.y * scale.y;\n"
		  " resized.z = point_array.z * scale.z;\n"
		  "	resized.w = 1;\n"
		  "	 resized = vec4(rotate(resized.xyz,vec3(1,0,0),M_PI * rotation.x/180),1);"
		  "	 resized = vec4(rotate(resized.xyz,vec3(0,1,0),M_PI * rotation.y/180),1);"
		  "	 resized = vec4(rotate(resized.xyz,vec3(0,0,1),M_PI * rotation.z/180),1);"
		  "	gl_Position = resized + position;\n"
		  "	TexPos = vec2(resized + position);\n"
		  "	pos = color_array;\n"
		  "}";
	  const std::string FshaderCode =
		  "#version 430\n"
		  "\n"
		  "layout(location = 0) out vec4 color;\n"
		  "layout(binding = 0) uniform sampler2D textur;"
		  "in vec4 pos;\n"
		  "in vec2 TexPos;\n"
		  "float k;"
		  "\n"
		  "void main()\n"
		  "{\n"
		  "	vec4 texColor = texture(textur, TexPos);\n"
		  "	color = pos;\n"
		  "}\n";
	  const std::string CshaderCode =
		"#version 430\n"
		"layout(local_size_x = 1, local_size_y = 1) in;\n"
		"layout(std140, binding = 5)  buffer Img_output\n"
		  "{\n"
		  "vec4 data[];\n"
		  "} img_output;\n"
		"void main() {\n"
			// base pixel colour for image
			"img_output.data[0] = vec4(4,4,4,4);\n"
			// get index in global work group i.e x,y position
		"}\n";


		public:  void Stat_CreateShader()
		{
			program = glCreateProgram();
			Cprogram = glCreateProgram();
			Vshader = Stat_CompileShader(VshaderCode, GL_VERTEX_SHADER);
			Fshader = Stat_CompileShader(FshaderCode, GL_FRAGMENT_SHADER);
			Cshader = Stat_CompileShader(CshaderCode, GL_COMPUTE_SHADER);
			glAttachShader(program, Vshader);
			glAttachShader(program, Fshader);
			glLinkProgram(program);
			glValidateProgram(program);


			glAttachShader(Cprogram, Cshader);
			glLinkProgram(Cprogram);
			glValidateProgram(Cprogram);

		}

	  static int Stat_CompileShader(const std::string& source, unsigned int Vertype)
	  {
		  unsigned int id = glCreateShader(Vertype);
		  const char* scr = source.c_str();
		  glShaderSource(id, 1, &scr, nullptr);
		  glCompileShader(id);

		  //error
		  int result;
		  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		  if (result == GL_FALSE)
		  {
			  int lenght;
			  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
			  char* message = new char[lenght];
			  glGetShaderInfoLog(id, lenght, &lenght, message);
			  std::cout << message << std::endl;
		  }
		  return id;
	  }
};

