#pragma once
#include <Texture.h>
#include <Custom.h>
namespace BeGL
{
	class GlFrameBuffer
	{
		uint32_t frameBuffer;
	public:
		Texture FrameBufferColorTexture;
		int mWidth, mHeight;
	public:
		GlFrameBuffer();
		GlFrameBuffer(int width, int height);
	public:
		void bind();
		void unbind();
	};
}