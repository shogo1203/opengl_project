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

	// ビュー変換行列を作成する
	// ex, ey, ez: 視点の位置
	// gx, gy, gz: 目標点の位置
	// ux, uy, uz: 上方向のベクトル
	static Matrix LookAt(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat gx, GLfloat gy, GLfloat gz, GLfloat ux, GLfloat uy, GLfloat uz);
	static Matrix Orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far);    // 直交投影変換行列を作成する
	static Matrix Frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat z_near, GLfloat z_far);    // 透視投影変換行列
	static Matrix Perspective(GLfloat fovy, GLfloat aspect, GLfloat z_near, GLfloat z_far);    // 画角を元に透視投影行列を作成する

	Matrix operator * (const Matrix& m) const;

private:
	GLfloat matrix_[16];
};

