#pragma once
#include <glew.h>
#include "object.h"
#include "model_asset.h"

class VertexObject : public Object
{
public:
	void Initialize(ModelAsset* model_data);
	void Finalize();
	void InitializeVertexBufferObject(GLsizei vertex_count, const Vertex* vertex);
	void InitializeIndexBufferObject(GLsizei index_count, const GLuint* index);
	void Draw() const;

private:
	GLuint vertex_array_object_;
	GLuint vertex_buffer_object_;
	GLuint index_buffer_object_;
	GLsizei index_count_;
	ModelAsset* model_data_;
};

