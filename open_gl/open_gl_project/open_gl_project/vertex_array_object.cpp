#include "vertex_array_object.h"

VertexArrayObject::VertexArrayObject(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index)
{
	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);

	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->color);
	glEnableVertexAttribArray(1);

	// インデックスの頂点バッファオブジェクト
	glGenBuffers(1, &index_buffer_object_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(GLuint), index, GL_STATIC_DRAW);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &vertex_array_object_);
	glDeleteBuffers(1, &vertex_buffer_object_);
	glDeleteBuffers(1, &index_buffer_object_);
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(vertex_array_object_);    // 描画する頂点配列オブジェクトを指定する
}
