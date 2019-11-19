#version 460 core
uniform mat4 modelview;
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 uv;

out vec2 vertex_uv;
out vec4 vertex_color;

void main()
{
    vertex_uv = uv;
	vertex_color = color;
	gl_Position = modelview * position;
}