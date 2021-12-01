#include "TestResourceManager.h"
#include "MonoStd/Timer.h"


namespace test {
	ResourceManager::ResourceManager()
	{
		loadShaders();
		loadTextures();
		loadMaterials();
		loadObjects();
	}
	ResourceManager::~ResourceManager()
	{
	}
	void ResourceManager::loadTextures()
	{
		Timer::LifeTimeTimer([](float time) {Log("texture load Time is:" << time);});
		woodTexture = Texture(woodTextureFileRef, Texture::TextureType::graphycsTexture);
		ironTexture = Texture(ironTextureFileRef, Texture::TextureType::graphycsTexture);
		rasterTexture = Texture(rasterTextureFileRef, Texture::TextureType::graphycsTexture);
		treeTexture = Texture(treeTextureFileRef, Texture::TextureType::graphycsTexture);
		bricksTexture = Texture(bricksTextureFileRef, Texture::TextureType::graphycsTexture);
		bricksNormalTexture = Texture(bricksNormalTextureFileRef, Texture::TextureType::graphycsTexture);
		cottageTexture = Texture(cottageTextureRef, Texture::TextureType::graphycsTexture);
		cottageNormalTexture = Texture(cottageNormalRef, Texture::TextureType::graphycsTexture);

		textTexture = Texture(textTextureFileRef, Texture::TextureType::text);
		btnTexture = Texture(btnTextureFileRef, Texture::TextureType::uI_texture);

	}
	void ResourceManager::loadObjects()
	{
		MonkeyObj.readObject("3DObjects\\Monkey.obj");
		TreeObj.readObject("3DObjects\\Tree.obj");
		RasterPlaneObj.readObject("3DObjects\\RasterPlaneV2.obj");
		sphereObj.readObject("3DObjects\\Sphere.obj");
		CottageObj.readObject("3DObjects\\cottage_obj.obj");
	}
	void ResourceManager::loadMaterials()
	{
		
		wireframe = Material("wireframe", 
			{ 
				shader::LayoutVertex::VecPoint, 
				shader::LayoutVertex::VecNormal, 
				shader::LayoutVertex::ColorRGBA 
			}, 
			sh2.shader, 
			Material::LayoutType::FaceStrip, 
			nullptr);
		flatface = Material("flatface",
			{
				shader::LayoutVertex::VecPoint,
				shader::LayoutVertex::VecNormal,
				shader::LayoutVertex::ColorRGBA
			},
			sh1.shader,
			Material::LayoutType::Triangles,
			nullptr);
		woodMaterial = Material("BetterMaterial", 
			{ 
				shader::LayoutVertex::VecPoint, 
				shader::LayoutVertex::VecNormal, 
				shader::LayoutVertex::VecTexture, 
				shader::LayoutVertex::ColorRGBA 
			}, 
			sh4.shader, 
			Material::LayoutType::Triangles, 
			&woodTexture);
		ironMaterial = Material("ironMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &ironTexture);
		treeMaterial = Material("treeMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &treeTexture);
		rasterMaterial = Material("rasterMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &rasterTexture);
		bricksMaterial = Material("bricksMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &bricksTexture);
		bricksNormalMat = Material("Bricks", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTangent,shader::LayoutVertex::VecBitangent,shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh5Normal.shader, Material::LayoutType::Triangles, &bricksTexture, &bricksNormalTexture);
		cottageMaterial = Material("cottage", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTangent,shader::LayoutVertex::VecBitangent,shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh5Normal.shader, Material::LayoutType::Triangles, &cottageTexture, &cottageNormalTexture);

	}
	void ResourceManager::loadShaders()
	{
		sh1.File_CreateShader("FlatShaded");
		Log("shader: " << sh1.program << ":\t" << sh1.shader.shaderName << "\n");
		sh2.File_CreateShader("wireframe");
		Log("shader: " << sh2.program << ":\t" << sh2.shader.shaderName << "\n");
		sh3.File_CreateShader("Material");
		Log("shader: " << sh3.program << ":\t" << sh3.shader.shaderName << "\n");
		sh4.File_CreateShader("Material2");
		Log("shader: " << sh4.program << ":\t" << sh4.shader.shaderName << "\n");
		sh5Normal.File_CreateShader("Mat3");
		Log("shader: " << sh5Normal.program << ":\t" << sh5Normal.shader.shaderName << "\n");
	}
}