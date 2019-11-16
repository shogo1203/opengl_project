#pragma once

#include <glew.h>
#include <vector>
#include "vertex.h"
#include <string>

struct ModelData
{
	//	頂点
	std::vector<Vertex> vertices;
	int vertices_count;
	// 頂点インデックス
	int indices_count;
	std::vector<GLuint> indices;
	// uv
	std::string uv_name;
	std::vector<GLfloat*> uv_points;
	std::vector<std::string> textures;
};