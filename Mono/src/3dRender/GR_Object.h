#pragma once
#include <Custom.h>
#include "Material.h"
#include <resourceManagment/FaceScript.h>
#include "BeGL/BeGL.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object
{
	bool MeshAloc = false;
	Object* parent;
	Vec3f getPosition();
public:
	Vec3f Position;
	Vec3f Rotation;
	Vec3f Scale;
	Vec3f ScreenScale;
	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	FaceScript faceScript;
	Material material;
	//Obj object_;
	unsigned int MeshSize;
	unsigned int MeshIndexSize;
	unsigned int MeshSizeB;
	unsigned int MeshIndexSizeB;
	/**
	* @brief Empty Constructor.
	* Creates an emptry object with no material and no mesh(cannot be drawn)
	*/
	Object();

	/**
	* @brief Default Constructor. 
	* @Param position Position of Object in World.
	* @Param scale Scale of Object in World.
	* @Param screenScale Scale of a screen As Vector in floats.
	* @Param material Material to be used to render Objects.
	*/
	Object(const Object&);
	Object(Object&&);
	Object(Vec3f position,
		Vec3f rotation, 
		Vec3f scale, 
		Vec3f screenScale, 
		Material material, 
		FaceScript faceScript, 
		Object* parent);
	~Object();
	Object& operator=(const Object&);
	void Destroy()
	{
		//delete[] Mesh;
		//delete[] MeshIndex;
	}
	float* GetMesh()
	{
		return mVertexBuffer;
	}
	unsigned int* GetMeshIndex()
	{
		return mIndexBuffer;
	}
	/**
		Sets Uniforms and Vertex Buffers
		Sets Uniforms and Vertex Buffers
	*/
	void graphicsInit()
	{
		glUseProgram(material.shaderScript.shaderID);
		BeGL::setUninformMat4f(material.shaderScript.rUniforms.uModelMatrix, ModelMatrix);
		glUniform4f(material.shaderScript.rUniforms.uModelMatrix, Position.x, Position.y, Position.z, 0);
		int missingUniform;
		if (material.shaderScript.rUniforms.uPosition != -1)
		{
			glUniform4f(material.shaderScript.rUniforms.uPosition, Position.x, Position.y, Position.z, 0);
		}
		else
		{
			Log("Cannot find Uniform Position");
		}
		if (material.shaderScript.rUniforms.uRotation != -1)
		{
			glUniform3f(material.shaderScript.rUniforms.uRotation, Rotation.x, Rotation.y, Rotation.z);
		}
		else
		{
			Log("Cannot find Uniform Rotation");
		}

		if (material.shaderScript.rUniforms.uScale != -1)
		{
			glUniform3f(material.shaderScript.rUniforms.uScale, Scale.x, Scale.y, Scale.z);
		}
		else
		{
			Log("Cannot find Uniform Scale");
		}

		if (material.shaderScript.rUniforms.uScreenScale != -1)
		{
			glUniform3f(material.shaderScript.rUniforms.uScreenScale, ScreenScale.x, ScreenScale.y, ScreenScale.z);
		}
		else
		{
			Log("Cannot find Uniform ScreenScale");
		}
		glGenBuffers(1, &mVertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, MeshSizeB, mVertexBuffer, GL_STATIC_DRAW);

		glGenBuffers(1, &mIndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MeshIndexSizeB, mIndexBuffer, GL_STATIC_DRAW);
	}
	void setViewMatrix(glm::mat4 viewMatrix)
	{
		ViewMatrix = viewMatrix;
	}
	void draw()
	{
		if (mVertexBuffer == nullptr)
		{
			return;
		}
		Vec3f lPosition = getPosition();
		glm::mat4 lTranslate = glm::translate(glm::mat4(1.0), glm::vec3(lPosition.x, lPosition.y, lPosition.z));
		glm::mat4 lScale = glm::scale(glm::mat4(1.0), glm::vec3(Scale.x, Scale.y, Scale.z));
		glm::mat4 lRotationX = glm::rotate(glm::mat4(1.0), -Rotation.x / 180 * (float)M_PI, glm::vec3(1, 0, 0));
		glm::mat4 lRotationY = glm::rotate(glm::mat4(1.0), Rotation.y / 180 * (float)M_PI, glm::vec3(0, 1, 0));
		glm::mat4 lRotationZ = glm::rotate(glm::mat4(1.0), Rotation.z / 180 * (float)M_PI, glm::vec3(0, 0, 1));

		ModelMatrix = lTranslate * lScale * lRotationX * lRotationY * lRotationZ;
		glm::mat4 RotationMatrix = lRotationX * lRotationY * lRotationZ;

		glUseProgram(material.shaderScript.shaderID);
		BeGL::setUninformMat4f(material.shaderScript.rUniforms.uModelMatrix, ModelMatrix);
		BeGL::setUniform4f(material.shaderScript.rUniforms.uPosition,Vec4f(lPosition,0));
		BeGL::setUninformMat4f(material.shaderScript.rUniforms.uRotation, RotationMatrix);
		//BeGL::setUniform3f(material.shaderScript.rUniforms.uRotation, Rotation);
		BeGL::setUniform3f(material.shaderScript.rUniforms.uScale, Scale);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObject);
		if (material.difuseTexture != nullptr)
		{
			material.difuseTexture->BindTo(0);
		}
		if (material.normalTexture != nullptr)
		{
			material.normalTexture->BindTo(1);
		}


		setAttribArray();

		glDrawElements(material.DrawMode, (unsigned int)(MeshIndexSize), GL_UNSIGNED_INT, nullptr);
	}
	void setAttribArray();
	void ChangeMaterial(Material material)
	{
		this->material = material;
	}
	unsigned int VertexLayout()
	{
		unsigned int VertexCount = 0;
		for (int i = material.VertexLayout.size() - 1; i >= 0; i--)
		{
			switch (material.VertexLayout[i])
			{
			case shader::LayoutVertex::VecPoint:
			{
				VertexCount += 3;
				break;
			}
			case shader::LayoutVertex::VecNormal:
			{
				VertexCount += 3;
				break;
			}
			case shader::LayoutVertex::VecTangent:
			{
				VertexCount += 3;
				break;
			}
			case shader::LayoutVertex::VecBitangent:
			{
				VertexCount += 3;
				break;
			}
			case shader::LayoutVertex::VecTexture:
			{
				VertexCount += 2;
				break;
			}
			case shader::LayoutVertex::ColorRGB:
			{
				VertexCount += 3;
				break;
			}
			case shader::LayoutVertex::ColorRGBA:
			{
				VertexCount += 4;
				break;
			}
			default:
				Log("Error while calculating vertex stride");
				break;
			}
		}
		return VertexCount;
	}
	/**
		Generates Vertex Layout from Specified Face Script

		Sets Uniforms and Vertex Buffers
	*/
	void GenMesh()
	{
		if (mVertexBuffer != nullptr)
		{
			delete[] mVertexBuffer;
			mVertexBuffer = nullptr;
			delete[] mIndexBuffer;
		}
		VertexSize = VertexLayout();
		switch (material.layoutType)
		{
		case Material::LayoutType::Triangles:
		{
			GenFlatFace();
			break;
		}
		case Material::LayoutType::FaceStrip:
		{
			GenWireframe();
			break;
		}
		case Material::LayoutType::FaceWire:
		{
			GenWireframe();
			break;
		}
		case Material::LayoutType::Points:
		{
			GenWireframe();
			break;
		}
		default:
			break;
		}
		GLuint buffersTodelete[2] = { mVertexBufferObject ,mIndexBufferObject };
		glDeleteBuffers(2, buffersTodelete);
		graphicsInit();
	}
	void GenWireframe()
	{
		MeshSize = 0;
		for (size_t i = 0; i < faceScript.Faces.size(); i++)
		{
			MeshSize += faceScript.Faces[i].VecPrt.size() * VertexSize;
		}
		mVertexBuffer = new float[MeshSize];
		MeshIndexSize = faceScript.Faces.size() * 8;
		mIndexBuffer = new unsigned int[MeshIndexSize];
		//unsigned int objBufferIndex[36];d
		int bufferPointer = 0;
		for (size_t i = 0; i < faceScript.Faces.size(); i++)
		{
			size_t k = 0;
			for (k = 0; k < faceScript.Faces[i].VecPrt.size(); k++)
			{
				size_t vertElement = 0;
				for (size_t v = 0; v < material.VertexLayout.size(); v++)
				{
					switch (material.VertexLayout[v])
					{
					case shader::LayoutVertex::VecPoint:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Vertex[faceScript.Faces[i].VecPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Vertex[faceScript.Faces[i].VecPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Vertex[faceScript.Faces[i].VecPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecNormal:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Normal[faceScript.Faces[i].NormalPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Normal[faceScript.Faces[i].NormalPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Normal[faceScript.Faces[i].NormalPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecTangent:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Tangent[faceScript.Faces[i].NormalPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Tangent[faceScript.Faces[i].NormalPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Tangent[faceScript.Faces[i].NormalPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecBitangent:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.BiTangent[faceScript.Faces[i].NormalPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.BiTangent[faceScript.Faces[i].NormalPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.BiTangent[faceScript.Faces[i].NormalPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecTexture:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Texture[faceScript.Faces[i].TexturePrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Texture[faceScript.Faces[i].TexturePrt[k]].y;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::ColorRGB:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::ColorRGBA:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.z;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = 1.0;
						vertElement++;
						break;
					}
					default:
						break;
					}
				}
			}
			bufferPointer += k * VertexSize;
		}
		int indexbufferPointer = 0;
		int indexVecrexPinter = 0;
		for (size_t i = 0; i < faceScript.Faces.size(); i++)
		{
			mIndexBuffer[indexbufferPointer + 0] = (indexVecrexPinter)+0;
			mIndexBuffer[indexbufferPointer + 1] = (indexVecrexPinter)+1;

			mIndexBuffer[indexbufferPointer + 2] = (indexVecrexPinter)+1;
			mIndexBuffer[indexbufferPointer + 3] = (indexVecrexPinter)+2;
			if (faceScript.Faces[i].VecPrt.size() == 4)
			{
				mIndexBuffer[indexbufferPointer + 4] = (indexVecrexPinter)+2;
				mIndexBuffer[indexbufferPointer + 5] = (indexVecrexPinter)+3;
				mIndexBuffer[indexbufferPointer + 6] = (indexVecrexPinter)+3;
				mIndexBuffer[indexbufferPointer + 7] = (indexVecrexPinter)+0;
				indexbufferPointer += 8;
				indexVecrexPinter += 4;
			}
			else
			{
				mIndexBuffer[indexbufferPointer + 4] = (indexVecrexPinter)+2;
				mIndexBuffer[indexbufferPointer + 5] = (indexVecrexPinter)+0;
				indexVecrexPinter += 3;
				indexbufferPointer += 6;
			}
		}
		MeshSizeB = MeshSize * sizeof(float);
		MeshIndexSizeB = MeshIndexSize * sizeof(unsigned int);
		MeshAloc = true;
	}
	void GenFlatFace()
	{
		MeshSize = 0;
		for (size_t i = 0; i < faceScript.Faces.size(); i++)
		{
			MeshSize += faceScript.Faces[i].VecPrt.size() * VertexSize;
		}
		mVertexBuffer = new float[MeshSize];
		MeshIndexSize = faceScript.Faces.size() * 6;
		mIndexBuffer = new unsigned int[MeshIndexSize];
		//unsigned int objBufferIndex[36];d
		int bufferPointer = 0;
		for (size_t i = 0; i < faceScript.Faces.size(); i++)
		{
			size_t k = 0;
			for (k = 0; k < faceScript.Faces[i].VecPrt.size(); k++)
			{
				int vertElement = 0;
				for (size_t v = 0; v < material.VertexLayout.size(); v++)
				{
					switch (material.VertexLayout[v])
					{
					case shader::LayoutVertex::VecPoint:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Vertex[faceScript.Faces[i].VecPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Vertex[faceScript.Faces[i].VecPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Vertex[faceScript.Faces[i].VecPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecNormal:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Normal[faceScript.Faces[i].NormalPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Normal[faceScript.Faces[i].NormalPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Normal[faceScript.Faces[i].NormalPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecTangent:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Tangent[faceScript.Faces[i].NormalPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Tangent[faceScript.Faces[i].NormalPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Tangent[faceScript.Faces[i].NormalPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecBitangent:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.BiTangent[faceScript.Faces[i].NormalPrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.BiTangent[faceScript.Faces[i].NormalPrt[k]].y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.BiTangent[faceScript.Faces[i].NormalPrt[k]].z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::VecTexture:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Texture[faceScript.Faces[i].TexturePrt[k]].x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Texture[faceScript.Faces[i].TexturePrt[k]].y;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::ColorRGB:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.z;
						vertElement++;
						break;
					}
					case shader::LayoutVertex::ColorRGBA:
					{
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.x;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.y;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = faceScript.Faces[i].Color.z;
						vertElement++;
						mVertexBuffer[bufferPointer + vertElement + (k * VertexSize)] = 1.0;
						vertElement++;
						break;
					}
					default:
						break;
					}
				}
			}
			bufferPointer += k * VertexSize;
		}
		int indexbufferPointer = 0;
		int indexVecrexPinter = 0;
		for (size_t i = 0; i < faceScript.Faces.size(); i++)
		{
			mIndexBuffer[indexbufferPointer + 0] = (indexVecrexPinter)+0;
			mIndexBuffer[indexbufferPointer + 1] = (indexVecrexPinter)+1;
			mIndexBuffer[indexbufferPointer + 2] = (indexVecrexPinter)+2;
			if (faceScript.Faces[i].VecPrt.size() == 4)
			{
				mIndexBuffer[indexbufferPointer + 3] = (indexVecrexPinter)+0;
				mIndexBuffer[indexbufferPointer + 4] = (indexVecrexPinter)+2;
				mIndexBuffer[indexbufferPointer + 5] = (indexVecrexPinter)+3;
				indexbufferPointer += 6;
				indexVecrexPinter += 4;
			}
			else
			{
				indexVecrexPinter += 3;
				indexbufferPointer += 3;
			}
		}
		MeshSizeB = MeshSize * sizeof(float);
		MeshIndexSizeB = MeshIndexSize * sizeof(unsigned int);
		MeshAloc = true;

	}


	void SetMaterial(Material material)
	{
		bool sameLayout = true;
		if (material.VertexLayout.size() == this->material.VertexLayout.size() && this->material.layoutType == material.layoutType)
		{
			for (size_t i = 0; i < material.VertexLayout.size(); i++)
			{
				if (material.VertexLayout[i] == this->material.VertexLayout[i])
				{
					sameLayout = false;
					break;
				}
			}
		}
		this->material = material;
		GenMesh();
	}
private:
	float* mVertexBuffer;
	unsigned int* mIndexBuffer;
	unsigned int mVertexBufferObject;
	unsigned int mIndexBufferObject;
	unsigned int VertexSize;
};