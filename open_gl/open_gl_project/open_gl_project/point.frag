#version 150 core
in vec4 vertex_color;
in vec2 vertex_uv;

out sampler2D texture;
out vec4 fragment;

void main()
{
	fragment = texture2D(texture, vertex_uv).rgb;
}