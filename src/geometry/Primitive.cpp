#include "sppch.h"
#include "Primitive.h"

namespace Surpass {

	MeshData Primitive::cube(float size)
	{
		MeshData data;
		float h = size * 0.5;
		data.vertices = {
			// +Z
			{{-h,-h, h}, { 0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f}}, {{ h,-h, h}, { 0.0f, 0.0f, 1.0f}, { 1.0f, 0.0f}},
			{{ h, h, h}, { 0.0f, 0.0f, 1.0f}, { 1.0f, 1.0f}}, {{-h, h, h}, { 0.0f, 0.0f, 1.0f}, { 0.0f, 1.0f}},
			// -Z
			{{ h,-h,-h}, { 0.0f, 0.0f,-1.0f}, { 0.0f, 0.0f}}, {{-h,-h,-h}, { 0.0f, 0.0f,-1.0f}, { 1.0f, 0.0f}},
			{{-h, h,-h}, { 0.0f, 0.0f,-1.0f}, { 1.0f, 1.0f}}, {{ h, h,-h}, { 0.0f, 0.0f,-1.0f}, { 0.0f, 1.0f}},
			// +X
			{{ h,-h, h}, { 1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f}}, {{ h,-h,-h}, { 1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f}},
			{{ h, h,-h}, { 1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f}}, {{ h, h, h}, { 1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f}},
			// -X
			{{-h,-h,-h}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f}}, {{-h,-h, h}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f}},
			{{-h, h, h}, {-1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f}}, {{-h, h,-h}, {-1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f}},
			// +Y
			{{-h, h, h}, { 0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f}}, {{ h, h, h}, { 0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f}},
			{{ h, h,-h}, { 0.0f, 1.0f, 0.0f}, { 1.0f, 1.0f}}, {{-h, h,-h}, { 0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f}},
			// -Y
			{{-h,-h,-h}, { 0.0f,-1.0f, 0.0f}, { 0.0f, 0.0f}}, {{ h,-h,-h}, { 0.0f,-1.0f, 0.0f}, { 1.0f, 0.0f}},
			{{ h,-h, h}, { 0.0f,-1.0f, 0.0f}, { 1.0f, 1.0f}}, {{-h,-h, h}, { 0.0f,-1.0f, 0.0f}, { 0.0f, 1.0f}}
		};
		
		for (int f = 0; f < 6; ++f)
		{
			unsigned int b = f * 4;
			data.indices.insert(data.indices.end(), {b, b + 1, b + 2, b + 0, b + 2, b + 3});
		}

		data.computeBounds();
		return data;
	}

	MeshData Primitive::sphere(float radius, int segments, int rings)
	{
		MeshData data;
		for (int ring = 0; ring <= rings; ++ring)
		{
			float ring_idx = (float)ring / rings;
			float phi = glm::pi<float>() * ring_idx;
			float y = radius * std::cos(phi);
			float r = radius * std::sin(phi);

			for (int seg = 0; seg <= segments; ++seg)
			{
				float seg_idx = (float)seg / segments;
				float theta = 2.0f * glm::pi<float>() * seg_idx;
				float x = r * std::cos(theta);
				float z = r * std::sin(theta);

				Vertex v;
				v.position = { x,y,z };
				v.normals = glm::normalize(glm::vec3(x, y, z));
				v.texCoord = { ring_idx, seg_idx };
				data.vertices.push_back(v);
			}
		}

		int stride = segments + 1;
		for (int ring = 0; ring < rings; ++ring)
		{
			for (int seg = 0; seg < segments; ++seg)
			{
				unsigned int v00 = ring * stride + seg;
				unsigned int v01 = v00 + 1;
				unsigned int v10 = (ring + 1) * stride + seg;
				unsigned int v11 = v10 + 1;

				data.indices.insert(data.indices.end(), {v00, v01, v11, v00, v11, v10});
			}
		}

		data.computeBounds();
		return data;
	}

	MeshData Primitive::plane(float width, float depth)
	{
		MeshData data;
		float w = width * 0.5f;
		float d = depth * 0.5f;

		Vertex v0, v1, v2, v3;
		v0.position = { -w, 0,-d };
		v0.normals = { 0, 1, 0 };
		v0.texCoord = { 0,0 };

		v1.position = { -w, 0, d };
		v1.normals = { 0, 1, 0 };
		v1.texCoord = { 0,1 };

		v2.position = { w, 0, d };
		v2.normals = { 0, 1, 0 };
		v2.texCoord = { 1,1 };

		v3.position = { w, 0, -d };
		v3.normals = { 0, 1, 0 };
		v3.texCoord = { 1,0 };

		data.vertices = { v0, v1, v2, v3 };
		data.indices = {
			0, 1, 2,
			0, 2, 3
		};

		data.computeBounds();
		return data;
	}
}