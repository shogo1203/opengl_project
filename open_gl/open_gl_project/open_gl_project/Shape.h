#pragma once
#include <memory>
#include "vertex_array_object.h"

class Shape
{
public:
	// size: ���_�̈ʒu�̎���
	// vertex_count: ���_�̐�
	// vertex: ���_�������i�[�����z��
	Shape(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count = 0, const GLuint* index = nullptr);
	void Draw() const;
	virtual void Execute() const;

protected:
	const GLsizei vertex_count_;    // �`��Ɏg�����_�̐�

private:
	std::shared_ptr<const VertexArrayObject> vertex_array_object_;    // �}�`�f�[�^
};

