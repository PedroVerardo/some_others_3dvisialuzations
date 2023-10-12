#version 410

uniform vec4 color;
uniform sampler2D face;
out vec4 fcolor;

in data{
	vec2 texcoord;
} f;

void main(void)
{
	fcolor = color * texture(face, f.texcoord);
}