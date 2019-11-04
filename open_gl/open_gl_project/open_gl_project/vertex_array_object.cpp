#include "vertex_array_object.h"

VertexArrayObject::VertexArrayObject(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index)
{
	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);

	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertex, GL_STATIC_DRAW);

	// ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ�����Q�Ƃł���悤�ɂ���
	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// �C���f�b�N�X�̒��_�o�b�t�@�I�u�W�F�N�g
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
	glBindVertexArray(vertex_array_object_);    // �`�悷�钸�_�z��I�u�W�F�N�g���w�肷��
}
