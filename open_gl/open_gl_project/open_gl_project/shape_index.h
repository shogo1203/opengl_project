#pragma once
#include "shape.h"

class ShapeIndex : public Shape
{
public:
	// size: ���_�̈ʒu�̎���
	// vertex_count: ���_�̐�
	// vertex: ���_�������i�[�����z��
	// index_count: ���_�̃C���f�b�N�X�̗v�f��
	// index: ���_�̃C���f�b�N�X���i�[�����z��
	ShapeIndex(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index);
	virtual void Execute() const;
protected:
	const GLsizei index_count_;
};

