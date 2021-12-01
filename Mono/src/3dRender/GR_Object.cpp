#include "GR_Object.h"

Vec3f Object::getPosition() {
	Vec3f lpos = Position;
	if (parent != nullptr)
	{
		lpos = lpos + parent->getPosition();
	}
	return lpos;
}
Object::Object() {
	this->Position = Vec3f(0.f, 0.f, 0.f);
	this->Rotation = Vec3f(0.f, 0.f, 0.f);
	this->Scale = Vec3f(1.f, 1.f, 1.f);
	this->ScreenScale = Vec3f(0.5626f, 1.0f, 1.0f);
	mVertexBuffer = nullptr;
}
Object::Object(const Object& other) {
	this->Position = other.Position;
	this->Rotation = other.Rotation;
	this->Scale = other.Scale;
	this->ScreenScale = other.ScreenScale;
	this->material = other.material;
	this->faceScript = other.faceScript;
	this->parent = other.parent;
	MeshSize = other.MeshSize;
	MeshSizeB = other.MeshSizeB;
	if (other.mVertexBuffer != nullptr && MeshSize>0) {
		mVertexBuffer = new float[MeshSize];
	}
	else {
		mVertexBuffer = nullptr;
	}
	MeshIndexSize = other.MeshIndexSize;
	MeshIndexSizeB = other.MeshIndexSizeB;
	if (other.mIndexBuffer != nullptr && MeshIndexSize >0) {
		mIndexBuffer = new unsigned int[MeshIndexSize];
	}
	else {
		mIndexBuffer = nullptr;
	}
	glm::mat4 lTranslate = glm::translate(glm::mat4(1.0), glm::vec3(Position.x, Position.y, Position.z));
	glm::mat4 lScale = glm::scale(glm::mat4(1.0), glm::vec3(Scale.x, Scale.y, Scale.z));
	glm::mat4 lRotationX = glm::rotate(glm::mat4(1.0), Rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 lRotationY = glm::rotate(glm::mat4(1.0), Rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 lRotationZ = glm::rotate(glm::mat4(1.0), Rotation.z, glm::vec3(0, 0, 1));
	ModelMatrix = lTranslate * lScale * lRotationX * lRotationY * lRotationZ;
}

Object::Object(Object&& other)
{
	this->Position = other.Position;
	this->Rotation = other.Rotation;
	this->Scale = other.Scale;
	this->ScreenScale = other.ScreenScale;
	this->material = other.material;
	this->faceScript = other.faceScript;
	this->parent = other.parent;
	MeshSize = other.MeshSize;
	MeshIndexSize = other.MeshIndexSize;
	MeshSizeB = other.MeshSizeB;
	MeshIndexSizeB = other.MeshIndexSizeB;
	if (other.mVertexBuffer != nullptr) {
		mVertexBuffer = other.mVertexBuffer;
		other.mVertexBuffer = nullptr;

	}
	else {
		mVertexBuffer = nullptr;
	}
	if (other.mIndexBuffer != nullptr) {
		mIndexBuffer = other.mIndexBuffer;
		other.mVertexBuffer = nullptr;
		other.MeshIndexSize = 0;
	}
	else {
		mIndexBuffer = nullptr;
	}



	glm::mat4 lTranslate = glm::translate(glm::mat4(1.0), glm::vec3(Position.x, Position.y, Position.z));
	glm::mat4 lScale = glm::scale(glm::mat4(1.0), glm::vec3(Scale.x, Scale.y, Scale.z));
	glm::mat4 lRotationX = glm::rotate(glm::mat4(1.0), Rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 lRotationY = glm::rotate(glm::mat4(1.0), Rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 lRotationZ = glm::rotate(glm::mat4(1.0), Rotation.z, glm::vec3(0, 0, 1));
	ModelMatrix = lTranslate * lScale * lRotationX * lRotationY * lRotationZ;
}

Object::Object(Vec3f position, 
	Vec3f rotation, Vec3f scale, 
	Vec3f screenScale, 
	Material material, 
	FaceScript faceScript, 
	Object* parent) 
{
	this->Position = position;
	this->Rotation = rotation;
	this->Scale = scale;
	this->ScreenScale = screenScale;
	this->material = material;
	this->faceScript = faceScript;
	this->parent = parent;
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;
	glm::mat4 lTranslate = glm::translate(glm::mat4(1.0), glm::vec3(Position.x, Position.y, Position.z));
	glm::mat4 lScale = glm::scale(glm::mat4(1.0), glm::vec3(Scale.x, Scale.y, Scale.z));
	glm::mat4 lRotationX = glm::rotate(glm::mat4(1.0), Rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 lRotationY = glm::rotate(glm::mat4(1.0), Rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 lRotationZ = glm::rotate(glm::mat4(1.0), Rotation.z, glm::vec3(0, 0, 1));
	ModelMatrix = lTranslate * lScale * lRotationX * lRotationY * lRotationZ;
};

Object::~Object()
{
	if (mVertexBuffer != nullptr)
	{
		delete[] mVertexBuffer;
		mVertexBuffer = nullptr;
		delete[] mIndexBuffer;
		mIndexBuffer = nullptr;
	}
}
Object& Object::operator=(const Object& other)
{
	this->Position = other.Position;
	this->Rotation = other.Rotation;
	this->Scale = other.Scale;
	this->ScreenScale = other.ScreenScale;
	this->material = other.material;
	this->faceScript = other.faceScript;
	this->parent = other.parent;
	MeshSize = other.MeshSize;
	MeshSizeB = other.MeshSizeB;
	if (other.mVertexBuffer != nullptr && MeshSize > 0) {
		mVertexBuffer = new float[MeshSize];
	}
	else {
		mVertexBuffer = nullptr;
	}
	MeshIndexSize = other.MeshIndexSize;
	MeshIndexSizeB = other.MeshIndexSizeB;
	if (other.mIndexBuffer != nullptr && MeshIndexSize > 0) {
		mIndexBuffer = new unsigned int[MeshIndexSize];
	}
	else {
		mIndexBuffer = nullptr;
	}
	glm::mat4 lTranslate = glm::translate(glm::mat4(1.0), glm::vec3(Position.x, Position.y, Position.z));
	glm::mat4 lScale = glm::scale(glm::mat4(1.0), glm::vec3(Scale.x, Scale.y, Scale.z));
	glm::mat4 lRotationX = glm::rotate(glm::mat4(1.0), Rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 lRotationY = glm::rotate(glm::mat4(1.0), Rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 lRotationZ = glm::rotate(glm::mat4(1.0), Rotation.z, glm::vec3(0, 0, 1));
	ModelMatrix = lTranslate * lScale * lRotationX * lRotationY * lRotationZ;
	return *this;
}

void Object::setAttribArray()
{

	unsigned int glAtrinbArrayIndex = 0;
	unsigned int VertexOffset = 0;

	for (size_t i = 0; i < material.VertexLayout.size(); i++)
	{
		switch (material.VertexLayout[i])
		{
		case shader::LayoutVertex::VecPoint:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 3;
			glAtrinbArrayIndex++;
			break;
		}
		case shader::LayoutVertex::VecNormal:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 3;
			glAtrinbArrayIndex++;
			break;
		}
		case shader::LayoutVertex::VecTangent:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 3;
			glAtrinbArrayIndex++;
			break;
		}
		case shader::LayoutVertex::VecBitangent:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 3;
			glAtrinbArrayIndex++;
			break;
		}
		case shader::LayoutVertex::VecTexture:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 2;
			glAtrinbArrayIndex++;
			break;
		}
		case shader::LayoutVertex::ColorRGB:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 3;
			glAtrinbArrayIndex++;
			break;
		}
		case shader::LayoutVertex::ColorRGBA:
		{
			glEnableVertexAttribArray(glAtrinbArrayIndex);
			glVertexAttribPointer(glAtrinbArrayIndex, 4, GL_FLOAT, GL_FALSE, sizeof(float) * VertexSize, (char*)(sizeof(float) * VertexOffset));
			VertexOffset += 4;
			glAtrinbArrayIndex++;
			break;
		}
		default:
			Log("Error while creating vertex layout");
			break;
		}
	}

}
