#pragma once
#include <glew.h>
#include <vector>
#include "vertex.h"
#include <string>
#include "texture_asset.h"
#include "material.h"
#include <opencv2/opencv.hpp>;
#include "asset.h"

struct Uv
{
	GLfloat point[2];
};

class ModelAsset : public Asset
{
public:
	void Initialize();    // modelDataの初期化処理
	void Finalize();    // 解放処理

	//	頂点
	Vertex* vertices_;
	int vertices_count_;
	GLsizei indices_count_;
	GLuint* indices_;

	// uv
	std::string uv_set_name_;
	std::vector<Uv> uv_points_;
	std::vector<std::string> texture_names_;
	std::vector<Material*> materials_;
	GLuint texture_id_;
	TextureAsset* main_image_;   // materialに複数テクスチャがある場合に合成したテクスチャを表示する

private:
	void LoadTexture();    // opgnglで画像を表示できるようにする
};
