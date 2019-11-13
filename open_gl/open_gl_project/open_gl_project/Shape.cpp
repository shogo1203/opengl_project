#include "shape.h"

Shape::Shape(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index) :
	vertex_array_object_(new VertexArrayObject(size, vertex_count, vertex, index_count, index)),
	index_count_(index_count),
	vertex_count_(vertex_count)
{
}

Shape::Shape(ModelData* model_data) :
	Shape(3, model_data->vertices_count, model_data->vertices.data(), model_data->indices_count, model_data->indices.data())
{
}

void Shape::Draw() const
{
	Execute();
}

void Shape::Execute() const
{
	glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
}
