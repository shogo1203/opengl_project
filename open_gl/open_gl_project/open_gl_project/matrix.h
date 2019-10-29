#pragma once
#include <algorithm>
#include <glew.h>
#include <cmath>

class Matrix
{
public:
	Matrix();
	Matrix(const GLfloat* matrix);
	const GLfloat* GetMatrix() const;
	void LoadIdentity();    // �P�ʍs���ݒ肷��
	static Matrix Identity();    // �P�ʍs����쐬����
	static Matrix Translate(GLfloat x, GLfloat y, GLfloat z);    // (x, y, z)�������s�ړ�����ϊ��s����쐬����
	static Matrix Scale(GLfloat x, GLfloat y, GLfloat z);    // (x, y, z)�{�Ɋg��k������ϊ��s����쐬����
	static Matrix Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);    // (x, y, z)������angle�̐��l������]����ϊ��s����쐬����
	static Matrix LookAt(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat gx, GLfloat gy, GLfloat gz, GLfloat ux, GLfloat uy, GLfloat uz);    // �r���[�ϊ��s����쐬����

	Matrix operator * (const Matrix& m) const;

private:
	GLfloat matrix_[16];
};

