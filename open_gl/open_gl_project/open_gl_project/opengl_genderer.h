#pragma once

#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "shape.h"
#include "window.h"
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class OpenGLRenderer
{
public:
	OpenGLRenderer(Shape* shape, const char* vert_path, const char* frag_path);
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
	Shape* shape_;
};