#include "model_data.h"

void ModelData::LoadTexture()
{
	cv::Mat mat;
	main_image_ = new ImageData();

	// マテリアルに複数
	if (materials_.size() > 1)
	{
		for (int i = 0; i < materials_.size(); i++) {

			if (mat.empty() && !materials_[i]->image_data_->mat.empty()) {
				mat = materials_[i]->image_data_->mat.clone();
			}
			else {
				if (!materials_[i]->image_data_->mat.empty()) {
					cv::add(mat, materials_[i]->image_data_->mat, mat);
				}
			}
		}
	}
	else if (materials_.size() == 1) {
		mat = materials_[0]->image_data_->mat.clone();
	}
	else {
		// materialがついていない場合は何もしない
		return;
	}

	main_image_->mat = mat.clone();

	// 画像を表示できるようにする
	cv::flip(main_image_->mat, main_image_->mat, 0);
	cv::cvtColor(main_image_->mat, main_image_->mat, cv::COLOR_RGB2BGR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glGenTextures(1, &texture_id_);    // テクスチャ作成
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glPixelStorei(GL_UNPACK_ALIGNMENT, main_image_->mat.step / main_image_->mat.elemSize());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, main_image_->mat.cols, main_image_->mat.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, main_image_->mat.ptr());    // テクスチャにデータを紐つける
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ModelData::Initialize()
{
	for (auto&& path : texture_names_) {
		Material* material = new Material();
		material->CreateTexture(path.c_str());
		materials_.push_back(material);
	}

	LoadTexture();
}

void ModelData::Finalize()
{
	delete main_image_;

	for (auto&& material : materials_) {
		material->Finalize();
	}
	delete this;
}
