#pragma once
#include <Custom.h>
#include <iostream>
#include <resourceManagment/TextureRes.h>
#include <GL/glew.h>

class Texture
{
public:
	bool textureAloc;
	unsigned char* mPixelBuffer;
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
	int mBPP;
	std::string mTexturePath;
	TextureRes* textureRes;
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
	Texture(const std::string texturePath, TextureType);

	Texture(int width, int height, TextureType);
	Texture(TextureRes* textureRes);
	Texture();
	/**
	* @brief Binds This Texture to texture slot 0
	*/
	void Bind();
	void BindTo(int textureSlot);
	uint32_t getTextureID();
	~Texture();
};