#pragma once
#include <fbxsdk.h>
#include <iostream>
#include "model_data.h"

class FbxLoader
{
public:
	FbxLoader();
	ModelData* Load(const char* path);

private:
	void ExpandNode(FbxNode* node, ModelData* data);
	void AddVertex(FbxNode* node, ModelData* data);
	void ExpandPolygonVertices(FbxMesh* mesh, ModelData* data);
	void AddPolygonVertex(FbxMesh *mesh, ModelData* data, int index_polygons);
};

