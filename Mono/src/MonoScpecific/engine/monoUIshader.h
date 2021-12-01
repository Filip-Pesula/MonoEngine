#pragma once
#include <string>
#include <GL/glew.h>
#include <Custom.h>

namespace monoEngine
{
	const std::string VShaderString =
		R"(
#version 430

layout(location = 0) in vec4 point_array;
layout(location = 1) in vec4 texture_array;
uniform vec4 uPosition;
uniform vec2 uScale;
uniform int drawColor;
uinform vec4 Color;
		
out vec2 v_TexCoord;

void main()
{
	gl_Position = point_array * uScale + uPosition;
	v_TexCoord = texture_array.xy;
};
	)";
	const std::string FShaderString =
		R"(
#version 430

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;
uniform sampler2D uTexture;
uniform int drawColor;
uinform vec4 Color;
void main()
{
	if(drawColor)
	{
		color = Color;
	}
	else
	{
		vec4 SubColor = texture(uTexture, v_TexCoord);
		color = SubColor;
	}
};
	)";
	static class ViewportShader
	{
		void CreateShader()
		{
			shaderID = glCreateProgram();
			int vertSh = CompileShader(VertShaderTxt, GL_VERTEX_SHADER);
			int fragSh = CompileShader(FragShaderTxt, GL_FRAGMENT_SHADER);
			glAttachShader(shaderID, vertSh);
			glAttachShader(shaderID, fragSh);
			glLinkProgram(shaderID);
			glValidateProgram(shaderID);

			glDeleteProgram(vertSh);
			glDeleteProgram(fragSh);

			rUniforms.uScale = glGetUniformLocation(shaderID, "uScale");
			rUniforms.uColor = glGetUniformLocation(shaderID, "uColor");
			rUniforms.uPosition = glGetUniformLocation(shaderID, "uPosition");
			rUniforms.uRotation = glGetUniformLocation(shaderID, "uRotation");
			rUniforms.uTexture = glGetUniformLocation(shaderID, "uTexture");
			rUniforms.uScreenScale = glGetUniformLocation(shaderID, "uScreenScale");
			rUniforms.uDrawmode = glGetUniformLocation(shaderID, "uDrawMode");
			rUniforms.uBorder = glGetUniformLocation(shaderID, "uBorder");
		}
		int CompileShader(const std::string& source, unsigned int Vertype)
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
				Log(message);
			}
			return id;
		}
	public:
		ViewportShader()
		{
			CreateShader();
			VertShaderTxt = VShaderString;
			FragShaderTxt = FShaderString;
		}
		struct RUniforms
		{
			int uPosition; //uPosition
			int uRotation; //uRotation
			int uScale;
			int uColor;
			int uScreenScale;
			int uTexture;
			int uDrawmode;
			int uBorder;
		};
		std::string shaderName;
		int shaderID;
		RUniforms rUniforms;
		std::string VertShaderTxt;
		std::string FragShaderTxt;


	};
}