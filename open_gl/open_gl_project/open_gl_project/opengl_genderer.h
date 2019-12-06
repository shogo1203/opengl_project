#pragma once
#include <glew.h>
#include <cstdlib>
#include <iostream>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "window.h"
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "vertex_object.h"
#include "transform.h"
#include "fbx_loader.h"

class OpenGLRenderer : public Component
{
public:
	void Initialize() override;
	void Draw() override;
	void Finalize() override;
	void SetTransform(Transform* transform);    // Ç±ÇÍÇåƒÇŒÇ»Ç¢Ç∆çsÇØÇ»Ç¢
	void LoadShader(const char* vertex_path, const char* fragment_path);
	void LoadModel(const char* model_path);
	ModelData* model_data_;

protected:

private:
	Transform* transform_;
	GLboolean PrintProgramInfoLog(GLuint program);
	GLboolean PrintShaderInfoLog(GLuint shader, const char* str);
	GLuint CreateProgram(const char* v_src, const char* f_src);
	bool ReadShaderSource(const char* name, std::vector < GLchar>& buffer);
	GLuint LoadProgram(const char* vert, const char* frag);
	GLuint program_;
	GLuint model_view_uniform_location_;
	GLuint projection_uniform_location_;
	VertexObject vertex_object_;
	GLuint texture_location_;
	GLuint uv_location_;
};
