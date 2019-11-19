#pragma once

struct Vertex
{
	GLfloat position[3];
	GLfloat color[4]{ 1, 1, 1, 1 };
	GLfloat normal[3];
	GLfloat uv[2];
};