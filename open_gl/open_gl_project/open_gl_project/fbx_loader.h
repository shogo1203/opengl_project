#pragma once
#include <fbxsdk.h>
#include <iostream>
#include "model_data.h"

class FbxLoader
{
public:
	static ModelData* Load(const char* path);

private:
	static void ExpandNode(FbxNode* node);    // ノードをすべて展開する
	static void LoadVertex(FbxMesh* mesh);    // メッシュの読み込み
	static void LoadVertexIndex(FbxMesh* mesh);    // 頂点インデックスの読み込み
	static void ReadAttributeType(FbxNode* node);    // ノードの属性を見てそれに応じた関数を呼ぶ
	static void PrintVector3(float x, float y, float z);
	static void LoadNormal(FbxMesh* mesh);    // 法線の読み込み
	static void LoadNormalByControllPointAndDirect(FbxGeometryElementNormal* normal);
	static void LoadUv(FbxMesh* mesh);    // uv取得
	static void ReadMaterial(FbxNode* node);
	static inline ModelData* model_data_ = nullptr;    // 読み込み時に生成する
	static void SelectUvMapping(FbxMesh* mesh, int index);
	static void LoadUvByControllPointAndDirect(FbxLayerElementUV* mesh);
};

