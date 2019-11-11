#include "fbx_loader.h"

ModelData* FbxLoader::Load(const char* path)
{
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

	FbxGeometryConverter geometry_converter(manager);
	geometry_converter.Triangulate(scene, true);

	FbxNode* fbx_node = scene->GetRootNode();
	ModelData* model_data = new ModelData();

	int mesh_count = scene->GetSrcObjectCount<FbxMesh>();

	for (int i = 0; i < mesh_count; i++)
	{
		FbxMesh* mesh = scene->GetSrcObject<FbxMesh>(i);

		int control_points_count = mesh->GetControlPointsCount();
		model_data->vertices_count += control_points_count;

		FbxLayer* layer = mesh->GetLayer(i);

		float a = 0.5f;
		for (int i = 0; i < control_points_count; i++)
		{
			if ((i % 2) == 0) {
				a = 1;
			}
			else {
				a = 0;
			}
			FbxVector4 control_point = mesh->GetControlPointAt(i);
			Vertex vertex;
			vertex.position[0] = static_cast<GLfloat>(control_point[0]);
			vertex.position[1] = static_cast<GLfloat>(control_point[1]);
			vertex.position[2] = static_cast<GLfloat>(control_point[2]);

			vertex.color[0] = a;
			vertex.color[1] = a;
			vertex.color[2] = a;
			vertex.color[3] = 0.1f;
			model_data->vertices.push_back(vertex);

			//std::cout << "x" << control_point[0] << std::endl;
			//std::cout << "y" << control_point[1] << std::endl;
			//std::cout << "z" << control_point[2] << std::endl;
		}

		ExpandPolygonVertices(mesh, model_data);
	}
	//ExpandNode(fbx_node, model_data);

	manager->Destroy();

	return model_data;
}

void FbxLoader::ExpandNode(FbxNode* node, ModelData* data)
{
	AddVertex(node, data);

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		ExpandNode(node->GetChild(i), data);
	}
}

void FbxLoader::AddVertex(FbxNode* node, ModelData* data)
{
	if (node->GetNodeAttribute() == nullptr)
	{
		return;
	}

	if (node->GetNodeAttribute()->GetAttributeType() != FbxNodeAttribute::eMesh)
	{
		return;
	}
	//std::cout << node->GetName() << std::endl;

	FbxMesh* mesh = node->GetMesh();

	int controlPointsCount = mesh->GetControlPointsCount();
	data->vertices_count += controlPointsCount;

	for (int i = 0; i < controlPointsCount; i++)
	{
		FbxVector4 control_point = mesh->GetControlPointAt(i);
		data->vertices.push_back({ static_cast<GLfloat>(control_point[0]), static_cast<GLfloat>(control_point[1]), static_cast<GLfloat>(control_point[2]) });

		//std::cout << "x" << control_point[0] << std::endl;
		//std::cout << "y" << control_point[1] << std::endl;
		//std::cout << "z" << control_point[2] << std::endl;
	}

	ExpandPolygonVertices(mesh, data);
}

void FbxLoader::ExpandPolygonVertices(FbxMesh* mesh, ModelData* data)
{
	int* polygon_vertices = mesh->GetPolygonVertices();

	int total_polygons = mesh->GetPolygonCount();

	for (int i = 0; i < total_polygons; i++)
	{
		AddPolygonVertex(mesh, data, i);
	}
}

void FbxLoader::AddPolygonVertex(FbxMesh* mesh, ModelData* data, int index_polygons)
{
	for (int i = 0; i < 3; i++)
	{
		data->indices_count++;
		int index = mesh->GetPolygonVertex(index_polygons, i);
		//std::cout << "index" << index << std::endl;
		data->indices.push_back(index);
	}
}

