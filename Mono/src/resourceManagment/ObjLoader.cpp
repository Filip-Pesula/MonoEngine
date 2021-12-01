#include "ObjLoader.h"

const char* ObjLoader::corruption_warning_message[4]={
"",
"unknown line",
"floating point unreadeable",
"unsigned integer unreadeable"
};

void ObjLoader::readObject(std::string filepath)
{
	std::ifstream file(filepath);
	if (file.is_open())
	{
		Timer::Timer timer;
		std::string line;
#ifdef Debug
		{
			std::ifstream nfile(filepath);
			std::string nline;
			int linecout = 0;
			Timer::LifeTimeTimer linecoutTimer([&](float time) {
				Log("Linecout " << linecout << " time: " << time);
				});
			while (getline(nfile, nline))
			{
				linecout++;
			}

		}
#endif // Debug
		while (getline(file, line, '\n'))
		{
			if (line[0] != '#')
			{
				//flieLines.push_back(line);
			}
			switch (line[0])
			{
			case '#':
			{
				break;
			}
			case 'o':
			{
				line.erase(0, 2);
				ObjName = line;
				break;
			}
			case 'm':
				if (line.find("mtllib ") == 0)
				{
					line.erase(0, 7);
					mtllib = line;
				}
				else
				{
					LogError("Unrecognized line: " << line);
				}
				break;
			case 's':
				//TODO finish smooth shading on/off
				if (line == "s off")
				{

				}
				else if (line == "s on")
				{

				}
				else
				{
					LogError("Unrecognized line: " << line);
				}
				break;
			case 'v':
			{
				switch (line[1])
				{
				case ' ':
				{
					line.erase(0, 2);
					vertexSt.push_back(line);
					break;
				}
				case 'n':
				{
					line.erase(0, 3);
					NormalSt.push_back(line);
					break;
				}
				case 't':
				{
					line.erase(0, 3);
					TextureSt.push_back(line);
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case 'f':
			{
				line.erase(0, 2);
				PointersSt.push_back(line);
				break;
			}
			default:
			{
				LogWarn("Unrecognized line: "<<line);
				coruption_warning_stack.push_back(4);
				break;
			}
			}
		}
		std::cout << "Obj file read successfully in:\t" << timer.Stop() << "s" << std::endl;

		createBuffers();
		std::cout << "Obj Generated successfully in:\t" << timer.Stop() << "s" << std::endl << std::endl;
	}
	else
	{
		std::cout << "nelze nalest:  " << filepath << std::endl;
	}
}

void ObjLoader::createBuffers()
{
	vertex.reserve(vertexSt.size());
	for (size_t i = 0; i < vertexSt.size(); i++)
	{
		Vec3<std::string_view> sVdata = getVecSv(vertexSt[i]);
		Vec3<float> fVdata = getVecfF(sVdata);
		vertex.push_back(Vec3f(fVdata.x, fVdata.y, fVdata.z));
	}
	Log("VertexLoaded");
	Normal.reserve(NormalSt.size());
	for (size_t i = 0; i < NormalSt.size(); i++)
	{
		Vec3<std::string_view> sVdata = getVecSv(NormalSt[i]);
		Vec3<float> fVdata = getVecfF(sVdata);
		
		Normal.push_back(Vec3f(fVdata.x, fVdata.y, fVdata.z));
	}
	Log("NormalLoaded");
	Tangent.reserve(TextureSt.size());
	for (size_t i = 0; i < TextureSt.size(); i++)
	{
		int dataOffset[2] = { 0,0 };
		for (size_t q = 0; q < TextureSt[i].size(); q++)
		{
			if (TextureSt[i][q] == ' ')
			{
				dataOffset[1] = q + 1;
				break;
			}
		}
		for (size_t q = dataOffset[1]; q < TextureSt[i].size(); q++)
		{
			if (TextureSt[i][q] == ' ')
			{
				dataOffset[2] = q + 1;
				break;
			}
		}
		int dataLenght;
		char xdata[10]; xdata[8] = '0'; xdata[9] = '\0';
		char ydata[10]; ydata[8] = '0'; ydata[9] = '\0';
		TextureSt[i].copy(xdata, dataOffset[1] - dataOffset[0] - 1, dataOffset[0]);
		TextureSt[i].copy(ydata, TextureSt[i].size() - dataOffset[1] - 1, dataOffset[1]);
		float fxdata = std::stof(std::string(xdata));
		float fydata = std::stof(std::string(ydata));
		Textures.push_back(Vec2f(fxdata, fydata));
	}
	Log("TextureSt");
	Pointers.reserve(PointersSt.size());
	for (size_t i = 0; i < PointersSt.size(); i++)
	{

		char pointer1[4][3][9];
		{
			size_t q = 0;
			for (size_t o = 0; o < 4; o++)
			{
				for (size_t k = 0; k < 3; k++)
				{
					size_t qk = 0;
					for (size_t h = 0; h < 8; h++)
					{
						pointer1[o][k][h] = '\0';
					}
					pointer1[o][k][8] = '\0';
					if (q < PointersSt[i].size())
					{
						while (PointersSt[i][q] != '/' && q < PointersSt[i].size() && PointersSt[i][q] != ' ')
						{
							pointer1[o][k][qk] = PointersSt[i][q];
							q++;
							qk++;
						}
					}
					q++;
				}
			}


			std::vector<Vec3i> SubVecPtr;
			SubVecPtr.reserve(4);
			SubVecPtr.push_back(Vec3i(std::stoi(std::string(pointer1[0][0])), std::stoi(std::string(pointer1[0][1])), std::stoi(std::string(pointer1[0][2]))));
			SubVecPtr.push_back(Vec3i(std::stoi(std::string(pointer1[1][0])), std::stoi(std::string(pointer1[1][1])), std::stoi(std::string(pointer1[1][2]))));
			SubVecPtr.push_back(Vec3i(std::stoi(std::string(pointer1[2][0])), std::stoi(std::string(pointer1[2][1])), std::stoi(std::string(pointer1[2][2]))));
			if (pointer1[3][0][0] == '\0')
			{
				//SubVecPtr.push_back(Vec3i(std::stoi(std::string(pointer1[2][0])), std::stoi(std::string(pointer1[2][1])), std::stoi(std::string(pointer1[2][2]))));
			}
			else
			{
				SubVecPtr.push_back(Vec3i(std::stoi(std::string(pointer1[3][0])), std::stoi(std::string(pointer1[3][1])), std::stoi(std::string(pointer1[3][2]))));
			}
			std::vector<int> VecPtr;
			VecPtr.reserve(4);
			std::vector<int> NormalPtr;
			NormalPtr.reserve(4);
			std::vector<int> TexturePtr;
			TexturePtr.reserve(4);
			bool isFlat = true;
			{
				int normalMem = SubVecPtr[0].z;
				for (size_t h = 1; h < SubVecPtr.size(); h++)
				{
					if (SubVecPtr[h].z != SubVecPtr[h - 1].z)
					{
						isFlat = false;
					}
				}
			}
			VecPtr.push_back(SubVecPtr[0].x - 1);
			VecPtr.push_back(SubVecPtr[1].x - 1);
			VecPtr.push_back(SubVecPtr[2].x - 1);
			if (SubVecPtr.size() == 4) { VecPtr.push_back(SubVecPtr[3].x - 1); }
			TexturePtr.push_back(SubVecPtr[0].y - 1);
			TexturePtr.push_back(SubVecPtr[1].y - 1);
			TexturePtr.push_back(SubVecPtr[2].y - 1);
			if (SubVecPtr.size() == 4) { TexturePtr.push_back(SubVecPtr[3].y - 1); }
			if (isFlat)
			{
				NormalPtr.push_back(SubVecPtr[0].z - 1);
				NormalPtr.push_back(SubVecPtr[1].z - 1);
				NormalPtr.push_back(SubVecPtr[2].z - 1);
				if (SubVecPtr.size() == 4) { NormalPtr.push_back(SubVecPtr[3].z - 1); }
				Pointers.push_back(face(VecPtr, NormalPtr, TexturePtr, Vec3f(1.0, 1.0, 1.0)));
			}
			else
			{
				NormalPtr.push_back(SubVecPtr[0].z - 1);
				NormalPtr.push_back(SubVecPtr[1].z - 1);
				NormalPtr.push_back(SubVecPtr[2].z - 1);
				if (SubVecPtr.size() == 4) { NormalPtr.push_back(SubVecPtr[3].z - 1); }
				Pointers.push_back(face(VecPtr, NormalPtr, TexturePtr, { 1.0,1.0,1.0 }));


				//Pointers.push_back(face(VecPtr, SubVecPtr[0].z - 1));
			}
		}

	}
	Log("PointersSt");
	Tangent = std::vector<Vec3f>(Normal.size(), Vec3f(0, 0, 0));
	BiTangent = std::vector<Vec3f>(Normal.size(), Vec3f(0, 0, 0));
	for (size_t i = 0; i < Pointers.size(); i++)
	{
		face curentTris = Pointers[i];

		Vec3f vx1 = vertex[curentTris.VecPrt[0]];
		Vec3f vx2 = vertex[curentTris.VecPrt[1]];
		Vec3f vx3 = vertex[curentTris.VecPrt[2]];

		Vec2f uv1 = Textures[curentTris.TexturePrt[0]];
		Vec2f uv2 = Textures[curentTris.TexturePrt[1]];
		Vec2f uv3 = Textures[curentTris.TexturePrt[2]];

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
	fs = FaceScript(Pointers, vertex, Normal, Tangent, BiTangent, Textures);


}

Vec3<std::string> ObjLoader::getVecS(const std::string& txt) throw(std::string)
{
	Vec3<size_t> dataOffset = { 0,0,0 };
	Vec3<size_t> dataOffsetE = { 0,0,0 };
	dataOffset.x = txt.find_first_of("0123456789-");
	dataOffsetE.x = txt.find_first_of(" \t/", dataOffset.x);
	dataOffset.y = txt.find_first_of("0123456789-", dataOffsetE.x);
	dataOffsetE.y = txt.find_first_of(" \t/", dataOffset.y);
	dataOffset.z = txt.find_first_of("0123456789-", dataOffsetE.y);
	dataOffsetE.z = txt.find_first_of(" \t\r\n\0", dataOffset.z);
	if (dataOffsetE.z == std::string::npos)
	{
		dataOffsetE.z = txt.size();
	}
	Vec3<std::string> strVec{ "","","" };
	if (dataOffsetE.x <= dataOffset.x || dataOffsetE.y <= dataOffset.y || dataOffsetE.z <= dataOffset.z)
	{
		throw std::string("could not read element of vector");
	}
	strVec.x = txt.substr(dataOffset.x, dataOffsetE.x - dataOffset.x);
	strVec.y = txt.substr(dataOffset.y, dataOffsetE.y - dataOffset.y);
	strVec.z = txt.substr(dataOffset.z, dataOffsetE.z - dataOffset.z);

	return strVec;
}

Vec3<std::string_view> ObjLoader::getVecSv(const std::string& txt) throw(std::string)
{
	Vec3<size_t> dataOffset = { 0,0,0 };
	Vec3<size_t> dataOffsetE = { 0,0,0 };
	dataOffset.x = txt.find_first_of("0123456789-");
	dataOffsetE.x = txt.find_first_of(" \t/", dataOffset.x);
	dataOffset.y = txt.find_first_of("0123456789-", dataOffsetE.x);
	dataOffsetE.y = txt.find_first_of(" \t/", dataOffset.y);
	dataOffset.z = txt.find_first_of("0123456789-", dataOffsetE.y);
	dataOffsetE.z = txt.find_first_of(" \t\r\n\0", dataOffset.z);
	if (dataOffsetE.z == std::string::npos)
	{
		dataOffsetE.z = txt.size();
	}
	Vec3<std::string_view> strVec;
	if (dataOffsetE.x <= dataOffset.x || dataOffsetE.y <= dataOffset.y || dataOffsetE.z <= dataOffset.z)
	{
		throw std::string("could not read element of vector");
	}
	strVec.x = std::string_view(txt.c_str() + (dataOffset.x*sizeof(char)), dataOffsetE.x - dataOffset.x);
	strVec.y = std::string_view(txt.c_str() + (dataOffset.y*sizeof(char)), dataOffsetE.y - dataOffset.y);
	strVec.z = std::string_view(txt.c_str() + (dataOffset.z*sizeof(char)), dataOffsetE.z - dataOffset.z);

	return strVec;
}

Vec3<float> ObjLoader::getVecfF(const Vec3<std::string>& vecS) throw(std::string)
{
	Vec3<float> v;
	for (size_t i = 0; i < Vec3<float>::SIZE; i++)
	{
		try {
			v[i] = std::stof(vecS[i]); 
		}
		catch (const std::invalid_argument& ia)
		{
			throw(std::string("could not parse element of vector: " + vecS[i]));
		}
	}
	return v;
}
Vec3<float> ObjLoader::getVecfF(const Vec3<std::string_view>& vecS) throw(std::string)
{
	Vec3<float> v;
	for (size_t i = 0; i < Vec3<float>::SIZE; i++)
	{
		try {
			v[i] = atof_l(vecS[i]);
		}
		catch (const std::invalid_argument& ia)
		{
			throw(std::string("could not parse element of vector: ") + std::string(vecS[i]));
		}
	}
	return v;
}

float ObjLoader::atof_l(std::string_view sw) throw(std::string)
{
	uint32_t mantis = 0;
	int16_t exp = 1;
	uint32_t sign =0;
	int i = 0;
	if (sw.find_first_not_of("0123456789-e.") != std::string_view::npos)
	{
		throw(std::string("could not parse float: ") + std::string(sw));
	}
	if (sw.find('e') != std::string_view::npos)
	{
		throw(std::string("parsting string with \"e\" not yet implemented"));
	}
	

	if (sw[0] == '-')
	{
		sign = (1<<31);
	}
	char* currentPtr = (char*)(sw.data() + sw.size()-1);
	while (currentPtr >= sw.data())
	{
		if (*currentPtr == '.') {
			exp = i;
		}
		else if (*currentPtr == '-') {}
		else
		{
			mantis += (*currentPtr - 48) * (uint32_t)pow(10,i);
			i++;
		}
		currentPtr--;
	}
	static_assert(sizeof(float) == sizeof(uint32_t));
	union {
		float retValF;
		uint32_t retValU;
	};
	retValF = (float)mantis / (float)pow(10, exp);
	retValU |= sign;
	return retValF;
}
