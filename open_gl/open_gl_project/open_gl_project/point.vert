#version 150 core
uniform mat4 modelview;
in vec4 position;
in vec4 color;
in vec4 normal;
out vec4 vertex_color;

void main()
{
	vertex_color = color * normal;
	gl_Position = modelview * position;
}