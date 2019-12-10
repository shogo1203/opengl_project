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
	static void LoadVertex(FbxMesh* mesh);    // メッシュの読み込み
	static void LoadVertexIndex(FbxMesh* mesh);    // 頂点インデックスの読み込み
	static void LoadNormal(FbxMesh* mesh);    // 法線の読み込み
	static void LoadNormalByControllPointAndDirect(FbxGeometryElementNormal* normal);
	static void LoadUv(FbxMesh* mesh);    // uv取得
	static void AddTexture(FbxProperty prop);
	static void LoadVertexColor(FbxMesh* mesh);
	static void LoadVertexColorByPolygonVertexAndIndexToDirect(FbxGeometryElementVertexColor* vertex_color);
	static void LoadMaterial(FbxSurfaceMaterial* mat);

	static inline ModelAsset* model_data_ = nullptr;    // 読み込み時に生成する
};
