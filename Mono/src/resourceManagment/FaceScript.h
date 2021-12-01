#pragma once
#include <Custom.h>

class face
{
public:
	enum class Facetype
	{
		Smooth, Flat
	};
public:
	std::vector<int> VecPrt;
	std::vector<int> NormalPrt;
	std::vector<int> TexturePrt;
	Vec3f Color;
	Facetype facetype;
public:
	face(std::vector<int> vecPtr, std::vector<int> normalPtr, std::vector<int> texturePrt, Vec3f color, Facetype facetaype = Facetype::Smooth)
	{
		this->facetype = Facetype::Smooth;
		this->VecPrt = vecPtr;
		this->NormalPrt = normalPtr;
		this->TexturePrt = texturePrt;
		this->Color = color;

	}
	face(std::vector<int> vecPtr, int normalPtr, Facetype facetaype = Facetype::Flat)
	{
		this->facetype = Facetype::Flat;
		this->VecPrt = vecPtr;
		this->NormalPrt.push_back(normalPtr);
	}
};
/**
* @brief Set of faces with coresponding verteice normals and texture coordinates.
* Each face is constructed of 3-4 vertecies in a clockwise order.
*/
class FaceScript
{
public:
	unsigned int facecount;
	std::vector<face> Faces;
	std::vector<Vec3f> Vertex;
	std::vector<Vec3f> Normal; 
	std::vector<Vec3f> Tangent; 
	std::vector<Vec3f> BiTangent; 
	std::vector<Vec2f> Texture;
	FaceScript():
		facecount(0)
	{

	}
	/**
	* @brief Complete Constructor
	* @param faces Collection of faces referencing to vertex, normal and texture colections.
	* @param vertex Collection vertexes to be referenced 3 flat Vector.
	* @param normal Collection normals to be referenced  3 flat Vector.
	* @param texture Collection textures to be referenced  2 flat Vector.
	*/
	FaceScript(std::vector<face> faces, std::vector<Vec3f> vertex, std::vector<Vec3f> normal, std::vector<Vec3f> tangent, std::vector<Vec3f> biTangent, std::vector<Vec2f> texture) :
		facecount((int)faces.size()),
		Faces(faces),
		Vertex(vertex),
		Normal(normal),
		Tangent(tangent),
		BiTangent(biTangent),
		Texture(texture)
	{
	}
};