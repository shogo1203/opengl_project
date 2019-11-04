#include "shape_index.h"

ShapeIndex::ShapeIndex(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index) :
	Shape(size, vertex_count, vertex, index_count, index),
	index_count_(index_count)
{
}

void ShapeIndex::Execute() const
{
	glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
}
