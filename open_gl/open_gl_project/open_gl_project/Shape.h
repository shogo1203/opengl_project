#pragma once
#include <memory>
#include "vertex_array_object.h"

class Shape
{
public:
	// size: 頂点の位置の次元
	// vertex_count: 頂点の数
	// vertex: 頂点属性を格納した配列
	Shape(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count = 0, const GLuint* index = nullptr);
	void Draw() const;
	virtual void Execute() const;

protected:
	const GLsizei vertex_count_;    // 描画に使う頂点の数

private:
	std::shared_ptr<const VertexArrayObject> vertex_array_object_;    // 図形データ
};

