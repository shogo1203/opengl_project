#include "shape.h"

Shape::Shape(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index) :
	vertex_array_object_(new VertexArrayObject(size, vertex_count, vertex, index_count, index)),
	vertex_count_(vertex_count)
{
}

void Shape::Draw() const
{
	vertex_array_object_->Bind();
	Execute();
}

void Shape::Execute() const
{
	glDrawArrays(GL_LINE_LOOP, 0, vertex_count_);    // Ü‚êü‚Å•`‰æ‚·‚é
}
