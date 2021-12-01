#pragma once

#include <string>

namespace UIShaders
{
	const std::string VShaderString = 
	R"(
#version 430

layout(location = 0) in vec2 point_array;
layout(location = 1) in vec2 texture_array;
uniform vec4 uPosition;
uniform vec2 uScale;
uniform vec4 uColor;
uniform int uDrawMode;
uniform float uBorder;
		
vec4 resized;
out vec4 SColor;
out vec2 v_TexCoord;

void main()
{
	if(uDrawMode == 2)
	{
		if(point_array.x < 0.3 && point_array.x > 0)
		{
			resized.x = 1 * uScale.x - uBorder;
		}
		else
		{
			if(point_array.x > -0.3 && point_array.x < 0)
			{
				resized.x = -1 * uScale.x + uBorder;
			}
			else
			{
				resized.x = point_array.x * uScale.x;
			}
		}

		if(point_array.y < 0.3 && point_array.y > 0)
		{
			resized.y = 1 * uScale.y - uBorder;
		}
		else
		{
			if(point_array.y > -0.3 && point_array.y < 0)
			{
				resized.y = -1 * uScale.y + uBorder;
			}
			else
			{
				resized.y = point_array.y * uScale.y;
			}
		}
	}
	else
	{
		resized.x = point_array.x * uScale.x;
		resized.y = point_array.y * uScale.y;
		resized.w = 0;
		resized.z = 0;
	}

	gl_Position = resized + uPosition;
	v_TexCoord = texture_array.xy;
	SColor = uColor;
};
	)";
	const std::string FShaderString = 
	R"(
#version 430

layout(location = 0) out vec4 color;
in vec4 SColor;
in vec2 v_TexCoord;
uniform sampler2D uTexture;
uniform int uDrawMode;
void main()
{
	if(uDrawMode == 0)
	{
		gl_FragDepth = 0;
		color = SColor;
	}
	else
	{
		//uTexture
		vec4 SubColor = texture(uTexture, v_TexCoord);
		color.xyz = (SColor.xyz * SColor.w) + (SubColor.xyz * (1 - SColor.w));
		color.w = SubColor.w;
	}
};
	)";
}

