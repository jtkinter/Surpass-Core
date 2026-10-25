#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace Surpass {

	struct MeshData;
	class Mesh;
	class Texture;
	struct Material;

	class ResourceManager 
	{
	public:
		Mesh* findMesh(const std::string& name);
		Mesh& loadMesh(const std::string& name, const std::string& path = "", bool computeTangents = false);
		Mesh& addMesh(const std::string& name, const MeshData& data);

		Texture* findTexture(const std::string& name);
		Texture& loadTexture(const std::string& path);
		Texture& loadTexture(const std::string& name, const std::string& path);
		Texture& addTexture(const std::string& name, int width, int height, const unsigned char* data);

		Material* findMaterial(const std::string& name);
		Material& addMaterial(const std::string& name, const Material& mat);

	private:
		std::unordered_map<std::string, std::unique_ptr<Mesh>> m_Meshes;
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_Textures;
		std::unordered_map<std::string, std::unique_ptr<Material>> m_Materials;
	};

}