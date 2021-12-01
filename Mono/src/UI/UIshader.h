#pragma once
namespace UI
{
	struct UIShader
	{
		UIShader(std::string vertShader, std::string fragShader)
		{
			VertShaderTxt = vertShader;
			FragShaderTxt = fragShader;
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