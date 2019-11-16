#pragma once
#include <fbxsdk.h>
#include <iostream>
#include "model_data.h"

class FbxLoader
{
public:
	static ModelData* Load(const char* path);

private:
	static void ExpandNode(FbxNode* node);    // �m�[�h�����ׂēW�J����
	static void LoadVertex(FbxMesh* mesh);    // ���b�V���̓ǂݍ���
	static void LoadVertexIndex(FbxMesh* mesh);    // ���_�C���f�b�N�X�̓ǂݍ���
	static void ReadAttributeType(FbxNode* node);    // �m�[�h�̑��������Ă���ɉ������֐����Ă�
	static void PrintVector3(float x, float y, float z);
	static void LoadNormal(FbxMesh* mesh);    // �@���̓ǂݍ���
	static void LoadNormalByControllPointAndDirect(FbxGeometryElementNormal* normal);
	static void LoadUv(FbxMesh* mesh);    // uv�擾
	static void ReadMaterial(FbxNode* node);
	static inline ModelData* model_data_ = nullptr;    // �ǂݍ��ݎ��ɐ�������
	static void SelectUvMapping(FbxMesh* mesh, int index);
	static void LoadUvByControllPointAndDirect(FbxLayerElementUV* mesh);
};

