#include "SampleObjects.h"

namespace SampleObjects
{
	FaceScript createSampleCube()
	{
		std::vector<Vec3f> vertex = { Vec3f(-0.5,-0.5,-0.5), Vec3f(-0.5,-0.5, 0.5), Vec3f(0.5, -0.5, 0.5),Vec3f(0.5, -0.5, -0.5),
			Vec3f(-0.5, 0.5,-0.5), Vec3f(-0.5, 0.5, 0.5), Vec3f(0.5, 0.5, 0.5),Vec3f(0.5, 0.5, -0.5) };
		std::vector<Vec3f> Normal = { Vec3f(0,-1,0),Vec3f(0,1,0),Vec3f(1,0,0),Vec3f(-1,0,0),Vec3f(0,0,1),Vec3f(0,0,-1) };
		std::vector<Vec3f> Tangent;
		std::vector<Vec3f> BiTangent;
		std::vector<Vec2f> Texture = { Vec2f(0,0),Vec2f(0,1),Vec2f(1,1),Vec2f(1,0) };
		std::vector<face> Pointers = {
			face({3,2,1,0},{0,0,0,0},{0,1,2,3}, Vec3f(1.0,0,0)),
			face({4,5,6,7},{1,1,1,1},{0,1,2,3}, Vec3f(0,1.0,0)),
			face({2,3,7,6},{2,2,2,2},{0,1,2,3}, Vec3f(0,0,1.0)),
			face({0,1,5,4},{3,3,3,3},{0,1,2,3}, Vec3f(0,1.0,1.0)),
			face({1,2,6,5},{4,4,4,4},{0,1,2,3}, Vec3f(1.0,0.0,1.0)),
			face({3,0,4,7},{5,5,5,5},{0,1,2,3}, Vec3f(1.0,1.0,1.0)),
		};
		Tangent = std::vector<Vec3f>(Normal.size(), Vec3f(0, 0, 0));
		BiTangent = std::vector<Vec3f>(Normal.size(), Vec3f(0, 0, 0));
		for (int i = 0; i < Pointers.size(); i++)
		{
			face curentTris = Pointers[i];

			Vec3f vx1 = vertex[curentTris.VecPrt[0]];
			Vec3f vx2 = vertex[curentTris.VecPrt[1]];
			Vec3f vx3 = vertex[curentTris.VecPrt[2]];

			Vec2f uv1 = Texture[curentTris.TexturePrt[0]];
			Vec2f uv2 = Texture[curentTris.TexturePrt[1]];
			Vec2f uv3 = Texture[curentTris.TexturePrt[2]];

			Vec3f norm1 = Normal[curentTris.NormalPrt[0]];
			Vec3f norm2 = Normal[curentTris.NormalPrt[1]];
			Vec3f norm3 = Normal[curentTris.NormalPrt[2]];

			Vec3f edge1 = vx2 - vx1;
			Vec3f edge2 = vx3 - vx1;
			Vec3f edge3 = vx3 - vx1;

			Vec2f deltaUV1 = uv2 - uv1;
			Vec2f deltaUV2 = uv3 - uv1;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			Vec3f tan;
			tan.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tan.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tan.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			Vec3f biTan;
			biTan.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			biTan.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			biTan.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			for (int normalPtr : curentTris.NormalPrt)
			{
				Tangent[normalPtr] = tan;
				BiTangent[normalPtr] = biTan;
			}
		}
		FaceScript fsc = FaceScript(Pointers, vertex, Normal, Tangent, BiTangent, Texture);
		return fsc;
	}
	FaceScript genCross() {
		std::vector<Vec3f> vertex = { Vec3f(1,0,0), Vec3f(-1, 0, 0), Vec3f(0, 1, 0),Vec3f(0, -1, 0),
			Vec3f(0, 0,1), Vec3f(0, 0, -1) };

		std::vector<face> Pointers = {
			face({ 0,1 }, { 0,0,0,0 }, { 0,0,0,0 }, Vec3f(1.0, 0, 0),face::Facetype::Flat),
			face({ 2,3 }, { 0,0,0,0 }, { 0,0,0,0 }, Vec3f(1.0, 0, 0),face::Facetype::Flat),
			face({ 4,5 }, { 0,0,0,0 }, { 0,0,0,0 }, Vec3f(1.0, 0, 0),face::Facetype::Flat)
		};
		FaceScript fsc = FaceScript(Pointers, vertex, std::vector<Vec3f>(), std::vector<Vec3f>(), std::vector<Vec3f>(), std::vector<Vec2f>());
		return fsc;
	}
}