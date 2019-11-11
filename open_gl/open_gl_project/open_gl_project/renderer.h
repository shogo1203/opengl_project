#pragma once

#include "fbx_loader.h"
#include "opengl_genderer.h"
#include "shape.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"

class Renderer
{
public:
	Renderer(const char* fbx_path, const char* vertex_shader_path, const char* fragment_shader_path, Window* window);
	void Draw()  const;
	void Finalize();
private:
	OpenGLRenderer* gl_renderer_;
	ModelData* fbx_data_;
	glm::quat quaternion_;
};

