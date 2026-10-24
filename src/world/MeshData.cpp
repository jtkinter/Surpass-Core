#include "sppch.h"

#include "MeshData.h"

namespace Surpass {

	void MeshData::computeTangents()
	{
		std::vector<glm::vec3> tanAccum(vertices.size(), glm::vec3(0.0f));
		std::vector<glm::vec3> bitAccum(vertices.size(), glm::vec3(0.0f));

		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto i0 = indices[i], i1 = indices[i + 1], i2 = indices[i + 2];

			Vertex& v0 = vertices[i0];
			Vertex& v1 = vertices[indices[i1]];
			Vertex& v2 = vertices[indices[i2]];
			glm::vec3 e1 = v1.position - v0.position;
			glm::vec3 e2 = v2.position - v1.position;
			glm::vec2 d1 = v1.texCoord - v0.texCoord;
			glm::vec2 d2 = v2.texCoord - v1.texCoord;

			float det = d1.x * d2.y - d1.y * d2.x;
			if (std::abs(det) < 1e-6) continue;
			
			glm::vec3 T = (d2.y * e1 - d1.y * e2) / det;
			glm::vec3 B = (d1.x * e2 - d2.x * e1) / det;

			tanAccum[i0] += T;
			tanAccum[i1] += T;
			tanAccum[i2] += T;

			bitAccum[i0] += B;
			bitAccum[i1] += B;
			bitAccum[i2] += B;
		}

		for (size_t i = 0; i < vertices.size(); ++i)
		{
			glm::vec3 N = glm::normalize(vertices[i].normals);
			glm::vec3 T = tanAccum[i];

			T -= N * glm::dot(N, T);
			if (glm::length(T) < 1e-6)
			{
				glm::vec3 up = std::abs(N.x) > 0.9f ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0);
				T = up - N * glm::dot(N, up);
			}
			T = glm::normalize(T);

			float w = (glm::dot(glm::cross(N, T), bitAccum[i]) < 0.0f) ? -1.0f : 1.0f;
			vertices[i].tangent = glm::vec4(T, w);
		}
	}
}