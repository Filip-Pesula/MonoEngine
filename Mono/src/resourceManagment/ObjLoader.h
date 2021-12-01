#pragma once
#include <Custom.h>
#include <fstream>
#include <iostream>
#include "FaceScript.h"
#include <future>
#include <MonoStd/Timer.h>
enum class corruption_enum {
	unknown_line = 1,
	floating_point_unreadeable,
	unsigned_integer_unreadeable,
};
class ObjLoader
{
	static const char* corruption_warning_message[]; 

	//std::future get
	std::vector<std::string> flieLines;
	std::vector<std::string> vertexSt;
	std::vector<std::string> NormalSt;
	std::vector<std::string> TextureSt;
	std::vector<std::string> PointersSt;
	
	std::vector<Vec3f> vertex;
	std::vector<Vec3f> Normal;
	std::vector<Vec3f> Tangent;
	std::vector<Vec3f> BiTangent;
	std::vector<Vec2f> Textures;
	std::vector<face> Pointers;
	std::string ObjName = "";
	void createBuffers();

	Vec3<std::string> getVecS(const std::string& txt) throw(std::string);
	Vec3<std::string_view> getVecSv(const std::string& txt) throw(std::string);
	Vec3<float> getVecfF(const Vec3<std::string>& vecS) throw(std::string);
	Vec3<float> getVecfF(const Vec3<std::string_view>& vecS) throw(std::string);
	float atof_l(std::string_view) throw(std::string);
	std::string mtllib;
	std::vector<uint16_t> coruption_warning_stack;
	uint32_t coruption_flag = 0;
public:
	FaceScript fs;
	float* objBufferData;
	unsigned int objBufferDataLenght;
	unsigned int* objBufferIndex;
	unsigned int objBufferIndexLenght;
	void readObject(std::string filepath);


#ifdef TEST
public:
	void test() {
		std::string testStr1 = "0.0111 0.1111 0";
		Vec3<std::string> test1 = getVecS(testStr1);
		Vec3<std::string> test1E("0.0111", "0.1111", "0");
		ASSERT_EQUALS(test1, test1E, "getVecS not working");
		std::string testStr2 = "  0.0111  0,1111\t 07   ";
		Vec3<std::string> test2 = getVecS(testStr2);
		Vec3<std::string> test2E("0.0111", "0,1111", "07");
		ASSERT_EQUALS(test2, test2E, "TrimTestNotWorking");
		std::string testStr3 = "  0.0111  0,1111\t    ";
		ASSERT_THROWS(getVecS(testStr3), std::string("could not read element of vector"), "throw not working");

		Vec3<float>test1f = getVecfF(test1);
		Vec3<float>test1fE(0.0111f, 0.1111f, 0.f);
		ASSERT_EQUALS(test1f, test1fE, "parse error");
		std::string_view teststr(test2E.x.c_str(),6);
		std::string datatestm = "0.0111";
		union {
			float retValn;
			uint32_t retValnU;
		};
		retValn = -0.0111f;
		union {
			float retValp;
			uint32_t retValpU;
		};
		retValp = 0.0111f;
		uint32_t mask = (0xff << 23);
		uint32_t mantisMask = 0x7fffff;
		uint32_t signMask = (1 << 31);
		uint32_t signI = retValnU & signMask;
		uint32_t signIp = retValpU & signMask;
		uint32_t mantn = retValnU & mantisMask;
		retValnU = retValnU & mantisMask;
		uint32_t mantp = retValpU & mantisMask;
		std::string_view teststrm(test2E.x.c_str(),6);
		float getval = atof_l(teststr);

	}
#endif

};
