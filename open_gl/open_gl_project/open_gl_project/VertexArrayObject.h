#pragma once
#include <glew.h>

class VertexArrayObject
{
public:
	struct Vertex
	{
		GLfloat position[2];
	};

	// size: ���_�̈ʒu�̎���
	// vertex_count: ���_�̐�
	// vertex: ���_�������i�[�����z��
	VertexArrayObject(GLint size, GLsizei vertex_count, const Vertex* vertex);
	virtual ~VertexArrayObject();
	void Bind() const;    // ���_�z��I�u�W�F�N�g�̌���
private:
	VertexArrayObject(const VertexArrayObject& vertex_array_object);    // �R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~
	VertexArrayObject& operator=(const VertexArrayObject& vertex_array_object);    // ����ɂ��R�s�[�̋֎~
	GLuint vertex_array_object_;    // ���_�z��I�u�W�F�N�g��
	GLuint vertex_buffer_object_;    // ���_�o�b�t�@�I�u�W�F�N�g��
};

