#pragma once
#include "shape.h"

class ShapeIndex : public Shape
{
public:
	// size: 頂点の位置の次元
	// vertex_count: 頂点の数
	// vertex: 頂点属性を格納した配列
	// index_count: 頂点のインデックスの要素数
	// index: 頂点のインデックスを格納した配列
	ShapeIndex(GLint size, GLsizei vertex_count, const Vertex* vertex, GLsizei index_count, const GLuint* index);
	virtual void Execute() const;
protected:
	const GLsizei index_count_;
};

