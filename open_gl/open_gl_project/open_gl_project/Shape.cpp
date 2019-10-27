#include "Shape.h"

Shape::Shape(GLint size, GLsizei vertex_count, const VertexArrayObject::Vertex* vertex) :
	vertex_array_object(new VertexArrayObject(size, vertex_count, vertex)),
	vertex_count(vertex_count)
{
}

void Shape::Draw() const
{
	vertex_array_object->Bind();
	Execute();
}

void Shape::Execute() const
{
	glDrawArrays(GL_LINE_LOOP, 0, vertex_count);    // Ü‚êü‚Å•`‰æ‚·‚é
}
