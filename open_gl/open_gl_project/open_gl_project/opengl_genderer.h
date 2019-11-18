#pragma once
#include <cstdlib>
#include <iostream>
#include <glew.h>
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

class OpenGLRenderer
{
public:
	OpenGLRenderer(const char* vert_path, const char* frag_path, ModelData* model_data);
	void Initialize();
	void Draw(glm::vec3 position, glm::vec3 scale, glm::quat rotation);
	void Finalize();

private:
	GLboolean PrintProgramInfoLog(GLuint program);
	GLboolean PrintShaderInfoLog(GLuint shader, const char* str);
	GLuint CreateProgram(const char* v_src, const char* f_src);
	bool ReadShaderSource(const char* name, std::vector < GLchar>& buffer);
	GLuint LoadProgram(const char* vert, const char* frag);
	GLuint program_;
	GLuint model_view_uniform_location_;
	GLuint projection_uniform_location_;
	ModelData* model_data_;
	VertexObject vertex_object_;
};