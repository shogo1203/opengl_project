#pragma once

#include <glew.h>
#include <vector>
#include "vertex.h"

struct ModelData
{
	std::vector<Vertex> vertices;
	int vertices_count;
	int indices_count;
	std::vector<GLuint> indices;
};