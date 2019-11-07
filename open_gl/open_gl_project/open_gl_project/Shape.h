#pragma once
#include <memory>
#include "vertex_array_object.h"
#include "model_data.h"

class Shape
{
public:
	// size: ���_�̈ʒu�̎���
	// vertex_count: ���_�̐�
	// vertex: ���_�������i�[�����z��
	Shape(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count = 0, const GLuint* index = nullptr);
	Shape(ModelData* model_data);
	void Draw() const;
	void Execute() const;

protected:
	GLsizei index_count_;
	GLsizei vertex_count_;

private:
	std::shared_ptr<const VertexArrayObject> vertex_array_object_;    // �}�`�f�[�^
};

