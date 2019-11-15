#include "fbx_loader.h"

ModelData* FbxLoader::Load(const char* path)
{
	// fbx sdk‰Šú‰»ˆ—
	FbxManager* manager = FbxManager::Create();
	FbxScene* scene = FbxScene::Create(manager, "");

	FbxImporter* importer = FbxImporter::Create(manager, "");
	importer->Initialize(path, -1, manager->GetIOSettings());
	bool isImporting = importer->Import(scene);

	if (!isImporting)
	{
		std::cerr << "faild import path:" << path << std::endl;
	}

	importer->Destroy();

	// ŽOŠpŒ`‚É•ÏŠ·
	FbxGeometryConverter geometry_converter(manager);
	geometry_converter.Triangulate(scene, true);

	// ƒ‚ƒfƒ‹‚Ì“Ç‚Ýž‚Ý
	FbxNode* fbx_node = scene->GetRootNode();
	model_data_ = new ModelData();

	ExpandNode(fbx_node);

	manager->Destroy();

	return model_data_;
}

void FbxLoader::ExpandNode(FbxNode* node)
{

	ReadAttributeType(node);

	if (node->GetChildCount() < 1)
	{
		return;
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		ExpandNode(node->GetChild(i));
	}
}

void FbxLoader::LoadVertex(FbxMesh* mesh)
{
	int controlPointsCount = mesh->GetControlPointsCount();
	model_data_->vertices_count += controlPointsCount;

	for (int i = 0; i < controlPointsCount; i++)
	{
		FbxVector4 point = mesh->GetControlPointAt(i);
		Vertex vertex;
		vertex.position[0] = point[0];
		vertex.position[1] = point[1];
		vertex.position[2] = point[2];

		vertex.color[0] = 0.5f;
		vertex.color[1] = 1;
		vertex.color[2] = 1;
		vertex.color[3] = 0.5f;
		model_data_->vertices.push_back(vertex);
	}
}

void FbxLoader::LoadVertexIndex(FbxMesh* mesh)
{
	for (int i = 0; i < mesh->GetPolygonCount(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			model_data_->indices_count++;
			int index = mesh->GetPolygonVertex(i, j);
			model_data_->indices.push_back(index);
		}
	}
}

void FbxLoader::ReadAttributeType(FbxNode* node)
{
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		FbxNodeAttribute::EType type = node->GetNodeAttributeByIndex(i)->GetAttributeType();

		switch (type)
		{
		case fbxsdk::FbxNodeAttribute::eUnknown:
			break;
		case fbxsdk::FbxNodeAttribute::eNull:
			break;
		case fbxsdk::FbxNodeAttribute::eMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eSkeleton:
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:
			LoadVertex(node->GetMesh());
			LoadVertexIndex(node->GetMesh());
			LoadNormal(node->GetMesh());
			break;
		case fbxsdk::FbxNodeAttribute::eNurbs:
			break;
		case fbxsdk::FbxNodeAttribute::ePatch:
			break;
		case fbxsdk::FbxNodeAttribute::eCamera:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraStereo:
			break;
		case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
			break;
		case fbxsdk::FbxNodeAttribute::eLight:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalReference:
			break;
		case fbxsdk::FbxNodeAttribute::eOpticalMarker:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsCurve:
			break;
		case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eBoundary:
			break;
		case fbxsdk::FbxNodeAttribute::eNurbsSurface:
			break;
		case fbxsdk::FbxNodeAttribute::eShape:
			break;
		case fbxsdk::FbxNodeAttribute::eLODGroup:
			break;
		case fbxsdk::FbxNodeAttribute::eSubDiv:
			break;
		case fbxsdk::FbxNodeAttribute::eCachedEffect:
			break;
		case fbxsdk::FbxNodeAttribute::eLine:
			break;
		}
	}
}

void FbxLoader::PrintVector3(float x, float y, float z)
{
	std::cout << "x" << x << std::endl;
	std::cout << "y" << y << std::endl;
	std::cout << "z" << z << std::endl;
}

void FbxLoader::LoadNormal(FbxMesh* mesh)
{
	int normal_count = mesh->GetElementNormalCount();
	for (int i = 0; i < normal_count; i++)
	{
		FbxGeometryElementNormal* normal = mesh->GetElementNormal(i);
		FbxGeometryElement::EMappingMode  mapping_mode = normal->GetMappingMode();
		FbxGeometryElement::EReferenceMode reference_mode = normal->GetReferenceMode();

		switch (mapping_mode)
		{
		case fbxsdk::FbxLayerElement::eNone:
			break;
		case fbxsdk::FbxLayerElement::eByControlPoint:

			switch (reference_mode)
			{
			case fbxsdk::FbxLayerElement::eDirect:
				LoadNormalByControllPointAndDirect(normal);
				break;
			case fbxsdk::FbxLayerElement::eIndex:
				break;
			case fbxsdk::FbxLayerElement::eIndexToDirect:
				break;
			}

			break;
		case fbxsdk::FbxLayerElement::eByPolygonVertex:
			break;
		case fbxsdk::FbxLayerElement::eByPolygon:
			break;
		case fbxsdk::FbxLayerElement::eByEdge:
			break;
		case fbxsdk::FbxLayerElement::eAllSame:
			break;
		}

	}
}

void FbxLoader::LoadNormalByControllPointAndDirect(FbxGeometryElementNormal* normal)
{
	for (int i = 0; i < normal->GetDirectArray().GetCount(); i++)
	{
		model_data_->vertices[i].normal[0] = static_cast<GLfloat>(normal->GetDirectArray().GetAt(i)[0]);
		model_data_->vertices[i].normal[1] = static_cast<GLfloat>(normal->GetDirectArray().GetAt(i)[1]);
		model_data_->vertices[i].normal[2] = static_cast<GLfloat>(normal->GetDirectArray().GetAt(i)[2]);
	}
}
