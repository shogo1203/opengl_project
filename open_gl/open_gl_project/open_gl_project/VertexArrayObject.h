#pragma once
#include <glew.h>

class VertexArrayObject
{
public:
	struct Vertex
	{
		GLfloat position[2];
	};

	// size: 頂点の位置の次元
	// vertex_count: 頂点の数
	// vertex: 頂点属性を格納した配列
	VertexArrayObject(GLint size, GLsizei vertex_count, const Vertex* vertex);
	virtual ~VertexArrayObject();
	void Bind() const;    // 頂点配列オブジェクトの結合
private:
	VertexArrayObject(const VertexArrayObject& vertex_array_object);    // コピーコンストラクタによるコピーを禁止
	VertexArrayObject& operator=(const VertexArrayObject& vertex_array_object);    // 代入によるコピーの禁止
	GLuint vertex_array_object_;    // 頂点配列オブジェクト名
	GLuint vertex_buffer_object_;    // 頂点バッファオブジェクト名
};

