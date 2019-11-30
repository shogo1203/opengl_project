#include "vertex_object.h"

VertexObject::VertexObject()
{
	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);
}

void VertexObject::Initialize(ModelData* model_data)
{
	model_data_ = model_data;
	InitializeVertexBufferObject(model_data->vertices_count_, model_data->vertices_.data());
	InitializeIndexBufferObject(model_data->indices_count_, model_data->indices_.data());
}

void VertexObject::Finalize()
{
	glDeleteVertexArrays(1, &vertex_array_object_);
	glDeleteBuffers(1, &vertex_buffer_object_);
	glDeleteBuffers(1, &index_buffer_object_);
}

void VertexObject::InitializeVertexBufferObject(GLsizei vertex_count, const Vertex* vertex)
{
	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->color);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->normal);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->uv);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}

void VertexObject::InitializeIndexBufferObject(GLsizei index_count, const GLuint* index)
{
	// インデックスの頂点バッファオブジェクト
	glGenBuffers(1, &index_buffer_object_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(GLuint), index, GL_STATIC_DRAW);

	index_count_ = index_count;
}

void VertexObject::Draw() const
{
	glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
}
