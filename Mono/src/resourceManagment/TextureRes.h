#pragma once
#include <Custom.h>
#include <iostream>
#include <GL/glew.h>

class TextureRes
{
public:
	bool textureAloc;
	unsigned char* mPixelBuffer;
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
	int mBPP;
	std::string mTexturePath;
	enum TextureType
	{
		text,
		graphycsTexture,
		uI_texture

	} textureType;
	/**
	* @brief Generetes Texture
	* @param texturePath Reference to the texture as a file on disk
	*/
	TextureRes(const std::string texturePath, TextureType);

	TextureRes(int width, int height, TextureType);
	TextureRes();
	/**
	* @brief Binds This Texture to texture slot 0
	*/
	void Bind();
	void BindTo(int textureSlot);
	uint32_t getTextureID();
	~TextureRes();
};