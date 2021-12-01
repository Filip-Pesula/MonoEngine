#pragma once
#include <Texture.h>
#include <Custom.h>
#include <resourceManagment/TextureRes.h>
#include <resourceManagment/ShaderLoader.h>
#include <resourceManagment/ObjLoader.h>
#include <3dRender/Material.h>
namespace test
{
	class ResourceManager
	{
	private:
		//textureStrings;
		const std::string woodTextureFileRef{ "Textures\\drevo.jpg" };
		const std::string ironTextureFileRef{ "Textures\\iron.jpg" };
		const std::string cubeTextureFileRef{ "Textures\\CubeTex.png" };
		const std::string rasterTextureFileRef{ "Textures\\Raster4k.png" };
		const std::string treeTextureFileRef{ "Textures\\TreeTexture.png" };
		const std::string bricksTextureFileRef{ "Textures\\BricksFlemishRed.jpg" };
		const std::string bricksNormalTextureFileRef{ "Textures\\BricksFlemishRedNormal.png" };
		const std::string cottageTextureRef{ "Textures\\cottage_diffuse.png" };
		const std::string cottageNormalRef{ "Textures\\cottage_normal.png" };
		//UI textures
		const std::string textTextureFileRef{ "Textures\\text\\Font1_1.bmp" };
		const std::string btnTextureFileRef{ "Textures\\btn.png" };

		void loadTextures();
		void loadObjects();
		void loadMaterials();
		void loadShaders();
	public:
		ResourceManager();
		~ResourceManager();

		shader_file sh1;
		shader_file sh2;
		shader_file sh3;
		shader_file sh4;
		shader_file sh5Normal;

		//Material woodsNormalMaterial;
		Material wireframe;
		Material flatface;
		Material woodMaterial;
		Material ironMaterial;
		Material treeMaterial;
		Material rasterMaterial;
		Material bricksMaterial;
		Material bricksNormalMat;
		Material cottageMaterial;

		ObjLoader MonkeyObj;
		ObjLoader TreeObj;
		ObjLoader RasterPlaneObj;
		ObjLoader CottageObj;
		ObjLoader sphereObj;

		//text
		Texture textTexture;
		Texture btnTexture;
		//ambient
		Texture woodTexture;
		Texture ironTexture;
		Texture rasterTexture;
		Texture treeTexture;
		Texture bricksTexture;
		Texture cottageTexture;
		//normal
		Texture bricksNormalTexture;
		Texture cottageNormalTexture;
	};
}


