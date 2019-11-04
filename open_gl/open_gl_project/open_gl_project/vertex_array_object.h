#pragma once
#include <glew.h>
#include "model_data.h"

class VertexArrayObject
{
public:
	// size: ���_�̈ʒu�̎���
	// vertex_count: ���_�̐�
	// vertex: ���_�������i�[�����z��
	// index_count: ���_�̃C���f�b�N�X�̗v�f��
	// index: ���_�̃C���f�b�N�X���i�[�����z��
	VertexArrayObject(GLint size, GLsizei vertex_count, const Vertex* vertex = nullptr, GLsizei index_count = 0, const GLuint* index = nullptr);
	virtual ~VertexArrayObject();
	void Bind() const;    // ���_�z��I�u�W�F�N�g�̌���

private:
	VertexArrayObject(const VertexArrayObject& vertex_array_object);    // �R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~
	VertexArrayObject& operator=(const VertexArrayObject& vertex_array_object);    // ����ɂ��R�s�[�̋֎~
	GLuint vertex_array_object_;    // ���_�z��I�u�W�F�N�g
	GLuint vertex_buffer_object_;    // ���_�o�b�t�@�I�u�W�F�N�g
	GLuint index_buffer_object_;    // �C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g
};

