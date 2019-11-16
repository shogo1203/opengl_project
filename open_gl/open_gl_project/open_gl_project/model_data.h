#pragma once

#include <glew.h>
#include <vector>
#include "vertex.h"
#include <string>

struct ModelData
{
	//	���_
	std::vector<Vertex> vertices;
	int vertices_count;
	// ���_�C���f�b�N�X
	int indices_count;
	std::vector<GLuint> indices;
	// uv
	std::string uv_name;
	std::vector<GLfloat*> uv_points;
	std::vector<std::string> textures;
};