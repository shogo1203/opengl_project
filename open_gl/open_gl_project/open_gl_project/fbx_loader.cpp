#include "fbx_loader.h"

ModelData* FbxLoader::Load(const char* path)
{
	// fbx sdk初期化処理
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

	// 三角形に変換
	FbxGeometryConverter geometry_converter(manager);
	geometry_converter.Triangulate(scene, true);

	// モデルの読み込み
	FbxNode* fbx_node = scene->GetRootNode();
	model_data_ = nullptr;
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

		vertex.color[0] = 1.0f;
		vertex.color[1] = 1.0f;
		vertex.color[2] = 1.0f;
		vertex.color[3] = 0.0f;
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
			LoadUv(node->GetMesh());
			ReadMaterial(node);
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

void FbxLoader::LoadUv(FbxMesh* mesh)
{
	int element_uv_count = mesh->GetElementUVCount();

	for (int i = 0; i < element_uv_count; i++)
	{
		SelectUvMapping(mesh, i);
	}
}

void FbxLoader::ReadMaterial(FbxNode* node)
{
	int material_count = node->GetMaterialCount();

	for (int i = 0; i < material_count; i++) {
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

		int layered_texture_count = prop.GetSrcObjectCount<FbxLayeredTexture>();

		if (0 < layered_texture_count) {
			int file_texture_count = prop.GetSrcObjectCount<FbxFileTexture>();

			if (0 < file_texture_count) {
				for (int j = 0; file_texture_count > j; j++) {
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture) {
						std::string texture_path = texture->GetRelativeFileName();
					}
				}
			}

			for (int j = 0; layered_texture_count > j; j++) {
				FbxLayeredTexture* layered_texture = prop.GetSrcObject<FbxLayeredTexture>(j);
				int textureCount = layered_texture->GetSrcObjectCount<FbxFileTexture>();

				for (int k = 0; textureCount > k; k++) {
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

					if (texture) {
						std::string texture_name = texture->GetRelativeFileName();
						std::string uv_set_name = texture->UVSet.Get().Buffer();

						std::cout << texture_name;
					}
				}
			}
		}
		else {
			int file_texture_count = prop.GetSrcObjectCount<FbxFileTexture>();

			if (0 < file_texture_count) {
				for (int j = 0; file_texture_count > j; j++) {
					FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(j);
					if (texture) {
						std::string texture_name = texture->GetRelativeFileName();
						std::string uv_set_name = texture->UVSet.Get().Buffer();

						//--- UVSet名を比較し対応しているテクスチャなら保持 ---//
				/*		if (uvSet.uvSetName == UVSetName) {
							uvSet.textures.push_back(textureName);
						}*/
					}
				}
			}
		}
	}
}

void FbxLoader::SelectUvMapping(FbxMesh* mesh, int index)
{
	FbxGeometryElementUV* uv = mesh->GetElementUV(index);
	FbxGeometryElement::EMappingMode mapping = uv->GetMappingMode();
	FbxGeometryElement::EReferenceMode reference = uv->GetReferenceMode();

	switch (mapping)
	{
	case fbxsdk::FbxLayerElement::eNone:
		break;
	case fbxsdk::FbxLayerElement::eByControlPoint:
		LoadUvByControllPointAndDirect(uv);
		break;
	case fbxsdk::FbxLayerElement::eByPolygonVertex:
		break;
	case fbxsdk::FbxLayerElement::eByPolygon:
		break;
	case fbxsdk::FbxLayerElement::eByEdge:
		break;
	case fbxsdk::FbxLayerElement::eAllSame:
		break;
	default:
		break;
	}
}
void FbxLoader::LoadUvByControllPointAndDirect(FbxLayerElementUV* uv)
{
	for (int i = 0; i < uv->GetDirectArray().GetCount(); i++)
	{
		GLfloat point[2];
		point[0] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(i)[0]);
		point[1] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(i)[1]);
		model_data_->uv_points.push_back(point);
	}
	std::cout << model_data_->uv_points[0];
}
//
//switch (reference)
//{
//case fbxsdk::FbxLayerElement::eDirect:
//	for (int i = 0; i < uv_index_count; i++)
//	{
//		GLfloat point[2];
//		point[0] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(uv_index->GetAt(i))[0]);
//		point[1] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(uv_index->GetAt(i))[1]);
//		model_data_->uv_points.push_back(point);
//		PrintVector3(point[0], point[1], 0);
//	}
//	model_data_->uv_name = uv->GetName();
//	break;
//case fbxsdk::FbxLayerElement::eIndex:
//	break;
//case fbxsdk::FbxLayerElement::eIndexToDirect:
//
//	for (int i = 0; i < uv_index_count; i++)
//	{
//		GLfloat point[2];
//		point[0] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(uv_index->GetAt(i))[0]);
//		point[1] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(uv_index->GetAt(i))[1]);
//		model_data_->uv_points.push_back(point);
//	}
//
//	model_data_->uv_name = uv->GetName();
//	std::cout << model_data_->uv_name;
//	break;
//}
//switch (reference)
//{
//case fbxsdk::FbxLayerElement::eDirect:
//	for (int i = 0; i < uv_index_count; i++)
//	{
//		GLfloat point[2];
//		point[0] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(uv_index->GetAt(i))[0]);
//		point[1] = static_cast<GLfloat>(uv->GetDirectArray().GetAt(uv_index->GetAt(i))[1]);
//		model_data_->uv_points.push_back(point);
//	}
//
//	model_data_->uv_name = uv->GetName();
//	std::cout << model_data_->uv_name;