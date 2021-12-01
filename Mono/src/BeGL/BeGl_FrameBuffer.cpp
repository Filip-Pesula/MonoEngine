#include "BeGL_FrameBuffer.h"

namespace BeGL
{
	GlFrameBuffer::GlFrameBuffer(){}
	GlFrameBuffer::GlFrameBuffer(int width, int height)
	{
		FrameBufferColorTexture = Texture(width, height, Texture::TextureType::uI_texture);
		mWidth = width;
		mHeight = height;
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glBindTexture(GL_TEXTURE_2D, this->FrameBufferColorTexture.getTextureID());
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->FrameBufferColorTexture.getTextureID(), 0);
#ifdef Debug
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		{
			Log("Framebuffer Complete");
		}
		else
		{
			Log("Framebuffer Not Complete!!!");
		}
#endif // Debug
	}
	void GlFrameBuffer::bind()
	{
		glViewport(0, 0, mWidth, mHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}
	void GlFrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}