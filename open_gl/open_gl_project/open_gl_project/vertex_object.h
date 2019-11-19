#pragma once
#include <glew.h>
#include "object.h"
#include "model_data.h"

class VertexObject : public Object
{
public:
	VertexObject();
	void Initialize(ModelData* model_data);
	void Finalize();
	void InitializeVertexBufferObject(GLsizei vertex_count, const Vertex* vertex);
	void InitializeIndexBufferObject(GLsizei index_count, const GLuint* index);
	void Draw() const;

private:
	VertexObject(const VertexObject& vertex_object);
	VertexObject& operator=(const VertexObject& vertex_object) { }
	GLuint vertex_array_object_;
	GLuint vertex_buffer_object_;
	GLuint index_buffer_object_;
	GLsizei index_count_;
	ModelData* model_data_;
};

