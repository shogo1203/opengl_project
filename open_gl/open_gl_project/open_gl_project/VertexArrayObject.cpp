#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(GLint size, GLsizei vertex_count, const Vertex* vertex)
{
	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);

	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vertex_array_object_);
	glDeleteBuffers(1, &vertex_buffer_object_);
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(vertex_array_object_);    // 描画する頂点配列オブジェクトを指定する
}
