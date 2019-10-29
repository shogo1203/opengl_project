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
	void LoadIdentity();    // 単位行列を設定する
	static Matrix Identity();    // 単位行列を作成する
	static Matrix Translate(GLfloat x, GLfloat y, GLfloat z);    // (x, y, z)だけ並行移動する変換行列を作成する
	static Matrix Scale(GLfloat x, GLfloat y, GLfloat z);    // (x, y, z)倍に拡大縮小する変換行列を作成する
	static Matrix Rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);    // (x, y, z)を軸にangleの数値だけ回転する変換行列を作成する
	static Matrix LookAt(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat gx, GLfloat gy, GLfloat gz, GLfloat ux, GLfloat uy, GLfloat uz);    // ビュー変換行列を作成する

	Matrix operator * (const Matrix& m) const;

private:
	GLfloat matrix_[16];
};

