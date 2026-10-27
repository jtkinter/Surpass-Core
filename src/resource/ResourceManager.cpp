#include "sppch.h"
#include "ResourceManager.h"

#include "renderer/Mesh.h"
#include "world/Material.h"
#include "world/MeshData.h"
#include "geometry/ObjLoader.h"

namespace Surpass {

	Mesh* ResourceManager::findMesh(const std::string& name)
	{
		auto it = m_Meshes.find(name);
		return it == m_Meshes.end() ? nullptr : it->second.get();
	}

	Texture* ResourceManager::findTexture(const std::string& name)
	{
		auto it = m_Textures.find(name);
		return it == m_Textures.end() ? nullptr : it->second.get();
	}

	Material* ResourceManager::findMaterial(const std::string& name)
	{
		auto it = m_Materials.find(name);
		return it == m_Materials.end() ? nullptr : it->second.get();
	}


	Mesh& ResourceManager::loadMesh(const std::string& name, const std::string& path, bool computeTangents)
	{
		if (Mesh* existing = findMesh(name)) 
			return *existing;

		const std::string& actualPath = path.empty() ? name : path;
		
		MeshData data = ObjLoader::load(actualPath);
		if (computeTangents)
			data.computeTangents();
		auto mesh = std::make_unique<Mesh>(data);
		Mesh& ref = *mesh;
		m_Meshes[name] = std::move(mesh);
		return ref;
	}

	Mesh& ResourceManager::addMesh(const std::string& name, const MeshData& data)
	{
		if (Mesh* existing = findMesh(name))
			return *existing;

		auto mesh = std::make_unique<Mesh>(data);
		Mesh& ref = *mesh;
		m_Meshes[name] = std::move(mesh);
		return ref;
	}

	Texture& ResourceManager::loadTexture(const std::string& name, const std::string& path)
	{
		if (Texture* existing = findTexture(name))
			return *existing;

		auto texture = std::make_unique<Texture>(path);
		Texture& ref = *texture;
		m_Textures[name] = std::move(texture);
		return ref;
	}

	Texture& ResourceManager::loadTexture(const std::string& path)
	{
		return loadTexture(path, path);
	}

	Texture& ResourceManager::addTexture(const std::string& name, int width, int height, const unsigned char* data)
	{
		if (Texture* existing = findTexture(name))
			return *existing;

		auto texture = std::make_unique<Texture>(width, height, data);
		Texture& ref = *texture;
		m_Textures[name] = std::move(texture);
		return ref;
	}

	Material& ResourceManager::addMaterial(const std::string& name, const Material& mat)
	{
		if (Material* existing = findMaterial(name))
			return *existing;

		auto material = std::make_unique<Material>(mat);
		Material& ref = *material;
		m_Materials[name] = std::move(material);
		return ref;
	}
}