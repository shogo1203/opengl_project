#pragma once

#include <glew.h>
#include <vector>

struct Vertex
{
	GLfloat position[3];
};

struct ModelData
{
	std::vector<Vertex> vertices;
	int vertices_count;
	int indices_count;
	std::vector<GLuint> indices;
};