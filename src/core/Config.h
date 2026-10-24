#pragma once

namespace Surpass {
	inline constexpr int DIFFUSE_IDX = 0;				// 漫反射 0
	inline constexpr int MAX_LIGHTS = DIFFUSE_IDX + 8;	// 灯光数量和灯光阴影共用 1~8
	inline constexpr int NORMAL_IDX = MAX_LIGHTS + 1;	// 法线贴图 9
}