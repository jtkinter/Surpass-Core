#include "sppch.h"
#include "ObjLoader.h"

#include <fstream>
#include <sstream>

namespace Surpass {

	struct VertexKey
	{
		int posIdx;
		int normIdx;
		int uvIdx;

		bool operator==(const VertexKey& other) const
		{
			return posIdx == other.posIdx && normIdx == other.normIdx && uvIdx == other.uvIdx;
		}
	};

	struct VertexHash
	{
		size_t operator()(const VertexKey& key) const
		{
			return std::hash<int>()(key.posIdx)
				^ std::hash<int>()(key.normIdx) << 1
				^ std::hash<int>()(key.uvIdx) << 2;
		}
	};

	ObjLoader::MeshData ObjLoader::load(const std::string& filepath)
	{
		MeshData result;

		std::ifstream file(filepath);
		if (!file.is_open())
		{
			Log::error("无法打开文件：", filepath);
			return result;
		}

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::unordered_map<VertexKey, unsigned int, VertexHash> vertexMap;

		std::string line;
		while (std::getline(file, line))
		{
			if (line.size() == 0 || line[0] == '#') continue;

			std::stringstream ss(line);
			std::string prefix;
			ss >> prefix;

			if (prefix == "v")
			{
				glm::vec3 pos;
				ss >> pos.x >> pos.y >> pos.z;
				positions.push_back(pos);
			}
			else if (prefix == "vt")
			{
				glm::vec2 uv;
				ss >> uv.x >> uv.y;
				texCoords.push_back(uv);
			}
			else if (prefix == "vn")
			{
				glm::vec3 normal;
				ss >> normal.x >> normal.y >> normal.z;
				normals.push_back(normal);
			}
			else if (prefix == "f")
			{
				std::string vertexStr;
				std::vector<unsigned int> faceIndices;

				while (ss >> vertexStr)
				{
					int posIdx = 0, normIdx = 0, uvIdx = 0;
					size_t firstSlash = vertexStr.find('/');
					if (firstSlash == std::string::npos) // 确定是 v
						posIdx = std::stoi(vertexStr);
					else
					{
						posIdx = std::stoi(vertexStr.substr(0, firstSlash));
						size_t secondSlash = vertexStr.find('/', firstSlash + 1);
						if (secondSlash == std::string::npos && firstSlash + 1 < vertexStr.size()) // 确定是 v/vt
							uvIdx = std::stoi(vertexStr.substr(firstSlash + 1));
						else if (secondSlash != std::string::npos) // 确定有两条杠
						{
							if (secondSlash > firstSlash + 1) // 确定有/vt/
								uvIdx = std::stoi(vertexStr.substr(firstSlash + 1, secondSlash - firstSlash - 1));
							if (secondSlash + 1 < vertexStr.size()) // 确定有/vn
								normIdx = std::stoi(vertexStr.substr(secondSlash + 1));
						}
					}

					int pIdx = posIdx - 1;
					int nIdx = normIdx > 0 ? normIdx - 1 : -1;
					int tIdx = uvIdx > 0 ? uvIdx - 1 : -1;
					VertexKey key{ pIdx, nIdx, tIdx };

					unsigned int index;
					auto it = vertexMap.find(key);
					if (it != vertexMap.end())
						index = it->second;
					else
					{
						Vertex v;
						v.position = positions[pIdx];
						v.normals = nIdx >= 0 && nIdx < normals.size() ? normals[nIdx] : glm::vec3(0.0f, 0.0f, 1.0f);
						v.texCoord = tIdx >= 0 && tIdx < texCoords.size() ? texCoords[tIdx] : glm::vec2(0.0f);
						index = (unsigned int)result.vertices.size();
						result.vertices.push_back(v);
						vertexMap[key] = index;
					}
					faceIndices.push_back(index);
				}

				if (faceIndices.size() == 3)
					result.indices.insert(result.indices.end(), faceIndices.begin(), faceIndices.end());
				else if (faceIndices.size() == 4)
				{
					result.indices.push_back(faceIndices[0]);
					result.indices.push_back(faceIndices[1]);
					result.indices.push_back(faceIndices[2]);
					result.indices.push_back(faceIndices[2]);
					result.indices.push_back(faceIndices[3]);
					result.indices.push_back(faceIndices[0]);
				}
				else if (faceIndices.size() > 4)
				{
					for (size_t i = 0; i + 1 < faceIndices.size(); ++i)
					{
						result.indices.push_back(faceIndices[0]);
						result.indices.push_back(faceIndices[i]);
						result.indices.push_back(faceIndices[i + 1]);
					}
				}
			}
		}

		Log::info(filepath, "加载完毕 | 顶点数：", result.vertices.size(), " | 索引数：", result.indices.size());
		return result;
	}

}