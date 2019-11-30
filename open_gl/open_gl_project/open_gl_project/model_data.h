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
	void Initialize();    // modelData�̏���������
	void Finalize();    // �������

	//	���_
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
	ImageData* main_image_;   // material�ɕ����e�N�X�`��������ꍇ�ɍ��������e�N�X�`����\������

private:
	void LoadTexture();    // opgngl�ŉ摜��\���ł���悤�ɂ���
};
