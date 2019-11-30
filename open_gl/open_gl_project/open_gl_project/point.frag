#version 460 core
in vec4 vertex_color;
in vec2 vertex_uv;
uniform sampler2D texture_2d;

out vec4 fragment;

void main()
{
	fragment = texture(texture_2d, vertex_uv) * vertex_color;
}