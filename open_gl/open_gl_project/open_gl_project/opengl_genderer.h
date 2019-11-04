#pragma once
#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "shape.h"
#include "window.h"
#include "matrix.h"

class OpenGLRenderer
{
public:
	OpenGLRenderer(Shape* shape, const char* vert_path, const char* frag_path, Window* window);
	void Initialize();
	void Draw();
	void Finalize();
private:
	GLboolean PrintProgramInfoLog(GLuint program);
	GLboolean PrintShaderInfoLog(GLuint shader, const char* str);
	GLuint CreateProgram(const char* v_src, const char* f_src);
	bool ReadShaderSource(const char* name, std::vector < GLchar>& buffer);
	GLuint LoadProgram(const char* vert, const char* frag);
	GLuint program_;
	GLuint model_view_uniform_location_;
	GLuint projection_uniform_location_;
	Shape* shape_;
	Window* window_;
};

/*

const GLuint program(LoadProgram("point.vert", "point.frag"));    // プログラムオブジェクトを作成

// uniform変数の場所を取得する
const GLuint model_view_unifrom_location(glGetUniformLocation(program, "modelview"));
const GLuint projection_uniform_location(glGetUniformLocation(program, "projection"));

std::unique_ptr<const Shape> shape(new ShapeIndex(3, 8, cube_vertex, 24, wireCubeIndex));


		glUseProgram(program);	// シェーダプログラムの使用開始

		//拡大縮小の変換行列を求める
		const GLfloat* const size(window.GetSize());
		const GLfloat fovy(window.GetScale() * 0.01f);
		const GLfloat aspect(size[0] / size[1]);
		const Matrix projection(Matrix::Perspective(fovy, aspect, 1.0f, 10.0f));

		const GLfloat* const location(window.GetLocation());
		const Matrix model(Matrix::Translate(location[0], location[1], 0.0f));    // モデル変換行列を求める
		const Matrix view(Matrix::LookAt(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));    // ビュー変換行列を求める
		const Matrix model_view(view * model);    // モデルビュー変換行列を求める

		// uniform変数に値を設定する
		glUniformMatrix4fv(model_view_unifrom_location, 1, GL_FALSE, model_view.GetMatrix());
		glUniformMatrix4fv(projection_uniform_location, 1, GL_FALSE, projection.GetMatrix());

		//描画処理
		shape->Draw();
		*/
