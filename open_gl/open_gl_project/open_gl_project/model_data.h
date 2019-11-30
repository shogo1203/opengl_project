#pragma once
#include <glew.h>
#include <vector>
#include "vertex.h"
#include <string>
#include "image_data.h"
#include "material.h"
#include <opencv2/opencv.hpp>;

struct Uv
{
	GLfloat point[2];
};

class ModelData
{
public:
	void Initialize();    // modelDataの初期化処理
	void Finalize();    // 解放処理

	//	頂点
	std::vector<Vertex> vertices_;
	int vertices_count_;
	int indices_count_;
	std::vector<GLuint> indices_;

	// uv
	std::string uv_set_name_;
	std::vector<Uv> uv_points_;
	std::vector<std::string> texture_names_;
	std::vector<Material*> materials_;
	GLuint texture_id_;
	ImageData* main_image_;   // materialに複数テクスチャがある場合に合成したテクスチャを表示する

private:
	void LoadTexture();    // opgnglで画像を表示できるようにする
};
