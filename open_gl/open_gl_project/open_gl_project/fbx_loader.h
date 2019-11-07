#pragma once
#include <fbxsdk.h>
#include <iostream>
#include "model_data.h"

class FbxLoader
{
public:
	static ModelData* Load(const char* path);

private:
	static void ExpandNode(FbxNode* node, ModelData* data);
	static void AddVertex(FbxNode* node, ModelData* data);
	static void ExpandPolygonVertices(FbxMesh* mesh, ModelData* data);
	static void AddPolygonVertex(FbxMesh* mesh, ModelData* data, int index_polygons);
};

