#pragma once
#include <glew.h>
#include <vector>
#include "vertex.h"
#include <string>
#include "image_data.h"

struct Uv
{
	GLfloat point[2];
};

struct ModelData
{
	//	頂点
	std::vector<Vertex> vertices;
	int vertices_count;
	// 頂点インデックス
	int indices_count;
	std::vector<GLuint> indices;
	// uv
	std::string uv_set_name;
	std::vector<Uv> uv_points;
	std::vector<std::string> textures;
	ImageData* image_data_;
};