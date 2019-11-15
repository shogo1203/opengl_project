#pragma once

#include <glew.h>
#include <vector>
#include "vertex.h"

struct ModelData
{
	//	���_
	std::vector<Vertex> vertices;
	int vertices_count;
	// ���_�C���f�b�N�X
	int indices_count;
	std::vector<GLuint> indices;
};