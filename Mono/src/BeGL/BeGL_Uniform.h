#pragma once
#include <Custom.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace BeGL
{
	/**
	* @brief sets uniform
	* @param uniform Reference to uniform
	*/
	inline void setUniform4f(int uniform, Vec4f Vertex)
	{
		glUniform4f(uniform, Vertex.x, Vertex.y, Vertex.z, Vertex.u);
	}
	inline void setUniform4f(int uniform, Color4 Color)
	{
		glUniform4f(uniform, Color.r, Color.g, Color.b, Color.a);
	}
	inline void setUniform4f(int uniform, float Common)
	{
		glUniform4f(uniform, Common, Common, Common, Common);
	}
	inline void setUniform4f(int uniform, float x, float y, float z, float w)
	{
		glUniform4f(uniform, x, y, z, w);
	}

	inline void setUniform3f(int uniform, Vec3f Vertex)
	{
		glUniform3f(uniform, Vertex.x, Vertex.y, Vertex.z);
	}
	inline void setUniform3f(int uniform, float Common)
	{
		glUniform3f(uniform, Common, Common, Common);
	}

	inline void setUniform2f(int uniform, Vec2f Vertex)
	{
		glUniform2f(uniform, Vertex.x, Vertex.y);
	}
	inline void setUniform2f(int uniform, float Common)
	{
		glUniform2f(uniform, Common, Common);
	}
	inline void setUniform2f(int uniform, float x, float y)
	{
		glUniform2f(uniform, x, y);
	}

	inline void setUninformMat4f(int uniform, glm::mat4 matrix)
	{
		glUniformMatrix4fv(uniform, 1, false, &matrix[0][0]);
	}
}