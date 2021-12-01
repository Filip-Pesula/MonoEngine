#include "BetterText.h"
namespace UI
{
	inline Unit BetterText::getTextWidth(const Unit& size, const std::string& text)
	{
		float textWidth = 0;
		for (size_t i = 0; i < text.length(); i++)
		{
			textWidth += font::getcharWith(text.at(i), 1);
		}
		return size * textWidth;
	}
	void BetterText::genText()
	{
		int textsize = mText.size();
		vertexBufferSize = 4 * 4 * textsize;
		indexBufferSize = 6 * textsize;
		if (vertexBuffer != nullptr)
		{
			delete[] vertexBuffer;
		}
		vertexBuffer = new float[vertexBufferSize];
		int collum = 0;
		int row = 0;
		float tSize = (float)textsize;
		for (size_t i = 0; i < textsize; i++)
		{
			vertexBuffer[i * 16 + 0] = (i + 0 - tSize / 2) / (tSize / 2); vertexBuffer[i * 16 + 1] = 1;
			vertexBuffer[i * 16 + 2] = font::getTopLeft(mText[i]).x;
			vertexBuffer[i * 16 + 3] = font::getTopLeft(mText[i]).y;
			vertexBuffer[i * 16 + 4] = (i + 1 - tSize / 2) / (tSize / 2); vertexBuffer[i * 16 + 5] = 1;
			vertexBuffer[i * 16 + 6] = font::getTopRight(mText[i]).x;
			vertexBuffer[i * 16 + 7] = font::getTopRight(mText[i]).y;
			vertexBuffer[i * 16 + 8] = (i + 1 - tSize / 2) / (tSize / 2); vertexBuffer[i * 16 + 9] = -1;
			vertexBuffer[i * 16 + 10] = font::getBotRight(mText[i]).x;
			vertexBuffer[i * 16 + 11] = font::getBotRight(mText[i]).y;
			vertexBuffer[i * 16 + 12] = (i + 0 - tSize / 2) / (tSize / 2); vertexBuffer[i * 16 + 13] = -1;
			vertexBuffer[i * 16 + 14] = font::getBotLeft(mText[i]).x;
			vertexBuffer[i * 16 + 15] = font::getBotLeft(mText[i]).y;
		}
		if (indexBuffer != nullptr)
		{
			delete[] indexBuffer;
		}
		indexBuffer = new unsigned int[indexBufferSize];
		for (size_t i = 0; i < textsize; i++)
		{
			unsigned int offset = i * 4;
			indexBuffer[i * 6 + 0] = offset;
			indexBuffer[i * 6 + 1] = offset + 1;
			indexBuffer[i * 6 + 2] = offset + 2;
			indexBuffer[i * 6 + 3] = offset + 2;
			indexBuffer[i * 6 + 4] = offset + 3;
			indexBuffer[i * 6 + 5] = offset;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexBufferSize, vertexBuffer, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexBufferSize, indexBuffer, GL_STATIC_DRAW);
	}
	BetterText::BetterText(Unit size, Color4 color, std::string text, Texture* texture, Vec2<Unit> position, UIelement* parent):
		UIelement(getTextWidth(size, text),size,position,parent),
		mTexture(texture),
		vertexBuffer(nullptr),
		vertexBufferSize(0),
		indexBuffer(nullptr),
		indexBufferSize(0),
		vertex(-1),
		index(-1),
		mSize(size),
		mText(text),
		mColor(color)
	{
		glGenBuffers(1, &this->vertex);
		glGenBuffers(1, &this->index);
		genText();
	}
	BetterText::BetterText(const BetterText& origin, UIelement* parent) noexcept :
		UIelement(origin,parent),
		mTexture(origin.mTexture),
		vertexBuffer(nullptr),
		vertexBufferSize(0),
		indexBuffer(nullptr),
		indexBufferSize(0),
		vertex(-1),
		index(-1),
		mSize(origin.mSize),
		mText(origin.mText),
		mColor(origin.mColor)
	{
		glGenBuffers(1, &this->vertex);
		glGenBuffers(1, &this->index);
		genText();
	}
	BetterText::BetterText(const BetterText& origin) noexcept :
		UIelement(origin),
		mTexture(origin.mTexture),
		vertexBuffer(nullptr),
		vertexBufferSize(0),
		indexBuffer(nullptr),
		indexBufferSize(0),
		vertex(-1),
		index(-1),
		mSize(origin.mSize),
		mText(origin.mText),
		mColor(origin.mColor)
	{
		glGenBuffers(1, &this->vertex);
		glGenBuffers(1, &this->index);
		genText();
	}
	BetterText::BetterText(BetterText&& move) noexcept :
		UIelement(move),
		mTexture(move.mTexture),
		vertexBuffer(move.vertexBuffer),
		vertexBufferSize(move.vertexBufferSize),
		indexBuffer(move.indexBuffer),
		indexBufferSize(move.indexBufferSize),
		vertex(move.vertex),
		index(move.index),
		mSize(move.mSize),
		mText(move.mText),
		mColor(move.mColor)
	{
		move.vertexBuffer = nullptr;
		move.indexBuffer = nullptr;
		move.vertex = 0;
		move.index = 0;
		//TODO remove dependenci on genText and test it
		genText();
	}
	BetterText& BetterText::operator=(const BetterText& copy) noexcept
	{
		mParent = copy.mParent;
		mSize = copy.mSize;
		mWidth = copy.mWidth;
		mHeight = copy.mHeight;
		mPosition = copy.mPosition;
		mColor = copy.mColor;
		mText = copy.mText;
		mTexture = copy.mTexture;
		genText();
		return *this;
	}
	BetterText& BetterText::operator=(BetterText&& move) noexcept
	{
		mParent = move.mParent;
		mSize = move.mSize;
		mWidth = move.mWidth;
		mHeight = move.mHeight;
		mPosition = move.mPosition;
		mColor = move.mColor;
		mText = move.mText;
		mTexture = move.mTexture;
		this->~BetterText();
		vertexBuffer = move.vertexBuffer;
		move.vertexBuffer = nullptr;
		indexBuffer = move.indexBuffer;
		move.indexBuffer = nullptr;
		vertex = move.vertex;
		move.vertex = 0;
		index = move.index;
		move.index = 0;
		genText();
		return *this;
	}
	void BetterText::setText(std::string text)
	{
		if (text != mText)
		{
			mText = text;
		}
		genText();
	}
	void BetterText::Draw(UIShader shader)
	{
		if (!getVisible())
		{
			return;
		}
		glUseProgram(shader.shaderID);
		glBindBuffer(GL_ARRAY_BUFFER, vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (char*)(sizeof(float) * 2));

		mTexture->Bind();
		UIShader::RUniforms Uniforms = shader.rUniforms;
		Vec2f lPosition = getPosition();
		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);

		BeGL::setUniform4f(Uniforms.uPosition, mG_Position.x, mG_Position.y, 0, 1);
		BeGL::setUniform4f(Uniforms.uColor, mColor);
		BeGL::setUniform2f(Uniforms.uScale, mG_Width, mG_Height);
		glUniform1i(Uniforms.uTexture, 0);
		glUniform1i(Uniforms.uDrawmode, DrawModes::plane_Texture);
		glUniform1f(Uniforms.uBorder, 0.1f);
		glDrawElements(GL_TRIANGLES, indexBufferSize, GL_UNSIGNED_INT, nullptr);
	}
	BetterText::~BetterText()
	{
		if (vertexBuffer != nullptr)
		{
			delete[] vertexBuffer;
		}
		if (vertexBuffer != nullptr)
		{
			delete[] indexBuffer;
		}
		glDeleteBuffers(1, &vertex);
		glDeleteBuffers(1, &index);
	}
	std::unique_ptr<UIelement> BetterText::clone(UIelement* parent)
	{
		return std::move(std::make_unique<BetterText>(*this, parent));
	}
}