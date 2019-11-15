#pragma once

#include "fbx_loader.h"
#include "opengl_genderer.h"
#include "shape.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"
#include "transform.h"

class Renderer
{
public:
	Renderer(const char* fbx_path, const char* vertex_shader_path, const char* fragment_shader_path, Transform* transform);
	void Draw()  const;
	void Finalize();
private:
	OpenGLRenderer* gl_renderer_;
	ModelData* fbx_data_;
	Transform* transform_;
};
