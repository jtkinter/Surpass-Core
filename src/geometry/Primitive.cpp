#include "sppch.h"
#include "Primitive.h"

namespace Surpass {

	Primitive::MeshData Primitive::cube(float size)
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

		return data;
	}

	Primitive::MeshData Primitive::sphere(float radius, int segments, int rings)
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

		return data;
	}
}