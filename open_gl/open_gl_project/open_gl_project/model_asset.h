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
	void Initialize();    // modelData�̏���������
	void Finalize();    // �������

	//	���_
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
	TextureAsset* main_image_;   // material�ɕ����e�N�X�`��������ꍇ�ɍ��������e�N�X�`����\������

private:
	void LoadTexture();    // opgngl�ŉ摜��\���ł���悤�ɂ���
};
