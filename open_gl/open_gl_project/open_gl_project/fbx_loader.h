#pragma once
#include <fbxsdk.h>
#include <iostream>
#include "model_asset.h"
#include <algorithm>
#include <array>

class FbxLoader
{
public:
	static ModelAsset* Load(const char* path);

private:
	static void LoadVertex(FbxMesh* mesh);    // ���b�V���̓ǂݍ���
	static void LoadVertexIndex(FbxMesh* mesh);    // ���_�C���f�b�N�X�̓ǂݍ���
	static void LoadNormal(FbxMesh* mesh);    // �@���̓ǂݍ���
	static void LoadNormalByControllPointAndDirect(FbxGeometryElementNormal* normal);
	static void LoadUv(FbxMesh* mesh);    // uv�擾
	static void AddTexture(FbxProperty prop);
	static void LoadVertexColor(FbxMesh* mesh);
	static void LoadVertexColorByPolygonVertexAndIndexToDirect(FbxGeometryElementVertexColor* vertex_color);
	static void LoadMaterial(FbxSurfaceMaterial* mat);

	static inline ModelAsset* model_data_ = nullptr;    // �ǂݍ��ݎ��ɐ�������
};
