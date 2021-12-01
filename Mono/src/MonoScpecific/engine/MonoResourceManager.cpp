#include "MonoResourceManager.h"
#include <src/3dRender/GR_Object.h>
#include <src/resourceManagment/SampleObjects.h>
namespace monoEngine {
	ResourceManager *ResourceManager::s_inst = nullptr;
	ResourceManager::ResourceManager():
		textTexture(textTextureFileRef, Texture::uI_texture),
		btnTexture(btnTextureFileRef, Texture::uI_texture),
		woodTexture(woodTextureFileRef, Texture::graphycsTexture),
		ironTexture(ironTextureFileRef,Texture::graphycsTexture),
		rasterTexture(rasterTextureFileRef,Texture::graphycsTexture),
		treeTexture(treeTextureFileRef,Texture::graphycsTexture),
		bricksTexture(bricksTextureFileRef,Texture::graphycsTexture),
		bricksNormalTexture(bricksNormalTextureFileRef,Texture::graphycsTexture),
		wireframe(
			"wireframe", 
			{
			shader::LayoutVertex::VecPoint,
			shader::LayoutVertex::VecNormal,
			shader::LayoutVertex::ColorRGBA
			},
			sh2.shader,
			Material::LayoutType::FaceStrip,
			nullptr),
		flatface("flatface",
			{
				shader::LayoutVertex::VecPoint,
				shader::LayoutVertex::VecNormal,
				shader::LayoutVertex::ColorRGBA
			},
			sh1.shader,
			Material::LayoutType::Triangles,
			nullptr),
		woodMaterial("BetterMaterial",
			{
				shader::LayoutVertex::VecPoint,
				shader::LayoutVertex::VecNormal,
				shader::LayoutVertex::VecTexture,
				shader::LayoutVertex::ColorRGBA
			},
			sh4.shader,
			Material::LayoutType::Triangles,
			&woodTexture)
	{
		MonkeyObj.readObject("3DObjects\\Monkey.obj");
		TreeObj.readObject("3DObjects\\Tree.obj");
		RasterPlaneObj.readObject("3DObjects\\RasterPlaneV2.obj");
		CottageObj.readObject("3DObjects\\Sphere.obj");
		cross = SampleObjects::genCross();


		loadShaders();

		crossMat = Material(
			"crossMat",
			{
			shader::LayoutVertex::VecPoint
			},
			sh2.shader,
			Material::LayoutType::FaceStrip,
			nullptr);


		ironMaterial = Material("ironMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &ironTexture);
		treeMaterial = Material("treeMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &treeTexture);
		rasterMaterial = Material("rasterMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &rasterTexture);
		bricksMaterial = Material("bricksMaterial", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh4.shader, Material::LayoutType::Triangles, &bricksTexture);
		bricksNormalMat = Material("Bricks", { shader::LayoutVertex::VecPoint, shader::LayoutVertex::VecNormal, shader::LayoutVertex::VecTangent,shader::LayoutVertex::VecBitangent,shader::LayoutVertex::VecTexture, shader::LayoutVertex::ColorRGBA }, sh5Normal.shader, Material::LayoutType::Triangles, &bricksTexture, &bricksNormalTexture);
		s_inst = this;
	}
	
	ResourceManager::~ResourceManager()
	{

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