#pragma once
#include <Custom.h>
#include <Textures/text/Font1_1Data.h>

namespace font
{
	//const float fontData[256];
	inline Vec2f getTopLeft(char textChar)
	{
		Vec2f ret;
		unsigned char textCharRef = textChar;
		unsigned char xSlot = textCharRef % 16;
		unsigned char ySlot = textCharRef / 16;
		ret.x = ((float)xSlot) / 16.0f;
		ret.y = 1.0f - (((float)ySlot) / 16.0f);
		return ret;
	}
	inline Vec2f getTopRight(char textChar)
	{
		Vec2f ret;
		unsigned char textCharRef = textChar;
		unsigned char xSlot = textCharRef % 16;
		unsigned char ySlot = textCharRef / 16;
		ret.x = ((float)xSlot) / 16.0f + (0.0625f * fontData[textChar] / 32.0f);
		ret.y = 1.0f - (((float)ySlot) / 16.0f);
		return ret;
	}
	inline Vec2f getBotLeft(char textChar)
	{
		Vec2f ret;
		unsigned char textCharRef = textChar;
		unsigned char xSlot = textCharRef % 16;
		unsigned char ySlot = textCharRef / 16;
		ret.x = ((float)xSlot) / 16.0f;
		ret.y = 1.0f - (((float)ySlot) / 16.0f + 0.0625f);
		return ret;
	}
	inline Vec2f getBotRight(char textChar)
	{
		Vec2f ret;
		unsigned char textCharRef = textChar;
		unsigned char xSlot = textCharRef % 16;
		unsigned char ySlot = textCharRef / 16;
		ret.x = ((float)xSlot) / 16.0f + (0.0625f * fontData[textChar] / 32.0f);
		ret.y = 1.0f - (((float)ySlot) / 16.0f + 0.0625f);
		return ret;
	}
	inline float getcharWith(char textChar, float charSize)
	{
		return(charSize * fontData[textChar] / 32);
	}

}