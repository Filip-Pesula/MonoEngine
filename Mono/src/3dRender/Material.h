#pragma once
#include <Custom.h>
#include <Texture.h>
#include <resourceManagment/ShaderLoader.h>
class Material
{
	class Uniform
	{
		std::string UniformName;
		enum UniformType
		{
			Vec3f,
			Vec4f,
			Vec2f,
			Vec1f,
		};
		unsigned int UniformIndex;
	};
public:
	enum LayoutType
	{
		Triangles, //drawn as shell
		FaceWire, //drawn as wireframe arround each face
		TriangleWire, //drawn as wireframe arround each triangle
		FaceStrip,
		TriangleStrip,
		Points //drawn as Points
	};
private:
	std::string ShaderRef;
	std::string Name;
public:
	Texture* difuseTexture;
	Texture* normalTexture;
	std::vector<shader::LayoutVertex> VertexLayout;
	LayoutType layoutType;
	unsigned int DrawMode;
	ShaderScript shaderScript;
	Material()
	{
		this->shaderScript.shaderID = -1;
		VertexLayout.push_back(shader::LayoutVertex::empty);
		this->Name = "nan";
		this->DrawMode = GL_TRIANGLES;
	}
	Material(std::string name)
	{
		this->shaderScript.shaderID = -1;
		VertexLayout.push_back(shader::LayoutVertex::empty);
		this->Name = name;
		this->DrawMode = GL_TRIANGLES;
	}
	/**
	* @brief Sets material for 3d object
	* @param name Sets name of Material (can be referenced later on)
	* @param vertexLayout Colection of Enums defining layout of each vertex in a vertex bufferu
	* @param shader Reference to already compiled shader
	* @param layoutType Defines drawing layout type for buffer indexing and drawing
	* @param materualTexture Defines texture to be drawn as a Color map
	*/
	Material(std::string name, std::vector<shader::LayoutVertex> vertexLayout, ShaderScript shader, LayoutType layoutType,Texture* materualTexture)
	{
		Name = name;
		this->VertexLayout = vertexLayout;
		this->shaderScript = shader;
		this->layoutType = layoutType;
		switch (layoutType)
		{
		case Material::Triangles:
			this->DrawMode = GL_TRIANGLES;
			break;
		case Material::FaceStrip:
			this->DrawMode = GL_LINES;
			break;
		case Material::TriangleStrip:
			this->DrawMode = GL_LINE_STRIP;
			break;
		case Material::Points:
			this->DrawMode = GL_POINTS;
			break;
		default:
			break;
		}
		this->difuseTexture = materualTexture;
		this->normalTexture = nullptr;
	}
	Material(std::string name, std::vector<shader::LayoutVertex> vertexLayout, ShaderScript shader, LayoutType layoutType,Texture* difuseTexture, Texture* normalTexture)
	{
		Name = name;
		this->VertexLayout = vertexLayout;
		this->shaderScript = shader;
		this->layoutType = layoutType;
		switch (layoutType)
		{
		case Material::Triangles:
			this->DrawMode = GL_TRIANGLES;
			break;
		case Material::FaceStrip:
			this->DrawMode = GL_LINES;
			break;
		case Material::TriangleStrip:
			this->DrawMode = GL_LINE_STRIP;
			break;
		case Material::Points:
			this->DrawMode = GL_POINTS;
			break;
		default:
			break;
		}
		this->difuseTexture = difuseTexture;
		this->normalTexture = normalTexture;
	}
	void setShader()
	{
		ShaderScript shader;
	}
	std::string getName()
	{
		return Name;
	}
};